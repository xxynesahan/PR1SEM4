#include "header.h"

vector<User> SimpleDB::loadUsers() {
    vector<User> users;
    ifstream file(USERS_FILE);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string part;
            vector<string> parts;

            while (getline(ss, part, ';')) {
                parts.push_back(part);
            }

            if (parts.size() == 4) {
                users.push_back({
                    parts[0], parts[1], parts[2],
                    parts[3] == "1"
                    });
            }
        }
        file.close();
    }
    return users;
}

bool SimpleDB::saveUsers(const vector<User>& users) {
    ofstream file(USERS_FILE);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.username << ";" << user.password << ";"
                << user.role << ";" << (user.hasVaultAccess ? "1" : "0") << endl;
        }
        file.close();
        return true;
    }
    return false;
}

vector<AccessAttempt> SimpleDB::loadAccessLogs() {
    vector<AccessAttempt> logs;
    ifstream file(LOGS_FILE);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string part;
            vector<string> parts;

            while (getline(ss, part, ';')) {
                parts.push_back(part);
            }

            if (parts.size() == 3) {
                logs.push_back({
                    parts[0], parts[1],
                    parts[2] == "1"
                    });
            }
        }
        file.close();
    }
    return logs;
}

bool SimpleDB::saveAccessLog(const AccessAttempt& log) {
    ofstream file(LOGS_FILE, ios::app);
    if (file.is_open()) {
        file << log.username << ";" << log.timestamp << ";"
            << (log.successful ? "1" : "0") << endl;
        file.close();
        return true;
    }
    return false;
}

void VaultDatabase::loadData() {
    users = db.loadUsers();
    accessLogs = db.loadAccessLogs();

    if (users.empty()) {
        users = {
            {"Юлиана", "123", "director", true},
            {"Карина", "456", "security", false},
            {"Вова", "789", "manager", true}
        };
        db.saveUsers(users);
    }
}

VaultDatabase::VaultDatabase() { loadData(); }

bool VaultDatabase::addUser(string username, string password, string role, bool hasAccess) {
    for (const auto& user : users) {
        if (user.username == username) return false;
    }
    users.push_back({ username, password, role, hasAccess });
    return db.saveUsers(users);
}

string VaultDatabase::authenticate(string username, string password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return user.role;
        }
    }
    return "";
}

bool VaultDatabase::attemptVaultAccess(string username) {
    for (const auto& user : users) {
        if (user.username == username && user.hasVaultAccess) {
            logAccessAttempt(username, true);
            return true;
        }
    }
    logAccessAttempt(username, false);
    return false;
}

void VaultDatabase::logAccessAttempt(string username, bool success) {
    time_t now = time(0);
    char timestamp[26];
    ctime_s(timestamp, sizeof timestamp, &now);
    accessLogs.push_back({ username, timestamp, success });
    db.saveAccessLog({ username, timestamp, success });
}

void VaultDatabase::showAccessLogs() {
    cout << "\nЖурнал доступа к хранилищу:\n";
    for (const auto& log : accessLogs) {
        cout << "Пользователь: " << log.username
            << " | Время: " << log.timestamp
            << " | Статус: " << (log.successful ? "Успешно" : "Отказано") << endl;
    }
}

vector<User> VaultDatabase::getUsersWithAccess() {
    vector<User> result;
    for (const auto& user : users) {
        if (user.hasVaultAccess) {
            result.
            push_back(user);
        }
    }
    return result;
}

bool VaultDatabase::removeUser(const string& username) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->username == username) {
            users.erase(it);
            return db.saveUsers(users);
        }
    }
    return false;
}

void adminMenu(VaultDatabase& db) {
    while (true) {
        cout << "\nМеню администратора:\n"
            << "1. Показать журнал доступа\n"
            << "2. Показать пользователей с доступом\n"
            << "3. Добавить пользователя\n"
            << "4. Удалить пользователя\n"
            << "5. Выйти\n"
            << "Выберите: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            db.showAccessLogs();
        }
        else if (choice == 2) {
            auto users = db.getUsersWithAccess();
            for (const auto& user : users) {
                cout << user.username << " (" << user.role << ") - "
                    << (user.hasVaultAccess ? "Доступ есть" : "Нет доступа") << endl;
            }
        }
        else if (choice == 3) {
            string username, password, role;
            bool hasAccess;

            cout << "Имя пользователя: ";
            cin >> username;
            cout << "Пароль: ";
            cin >> password;
            cout << "Роль (manager/security/director): ";
            cin >> role;
            cout << "Доступ к хранилищу (1/0): ";
            cin >> hasAccess;

            if (db.addUser(username, password, role, hasAccess)) {
                cout << "Пользователь добавлен.\n";
            }
            else {
                cout << "Ошибка: пользователь уже существует.\n";
            }
        }
        else if (choice == 4) {
            string username;
            cout << "Введите имя пользователя для удаления: ";
            cin >> username;

            if (db.removeUser(username)) {
                cout << "Пользователь удален.\n";
            }
            else {
                cout << "Пользователь не найден.\n";
            }
        }
        else if (choice == 5) {
            break;
        }
    }
}

void userMenu(VaultDatabase& db, string username) {
    while (true) {
        cout << "\nМеню пользователя:\n"
            << "1. Попытаться открыть хранилище\n"
            << "2. Выйти\n"
            << "Выберите: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            if (db.attemptVaultAccess(username)) {
                cout << "Доступ разрешен. Хранилище открыто.\n";
            }
            else {
                cout << "Доступ запрещен. У вас нет прав для открытия хранилища.\n";
            }
        }
        else if (choice == 2) {
            break;
        }
    }
}
