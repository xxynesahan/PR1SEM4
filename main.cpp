#include "header.h"

void menu(DataBase& db, string role) {
    while (true) {
        cout << "\nМеню " << role << + "а:" << " \n1.Просмотреть тесты\n2.Выйти\nВыберите: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            auto tests = db.getTest(role);
            for (auto& i : tests) {
                cout << " " << i.name << ": " << i.description << endl;
            }
        }
        else if (choice == 2)
            break;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    DataBase db;
    while (true) {
        cout << "1. Войти\n2. Зарегистрироваться\n3. Выйти\nВыберите: ";
        int choice;
        cin >> choice;
        if (choice == 3)
            break;

        string username, password, role;
        cout << "Имя: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        if (choice == 1) {
            role = db.getRole(username, password);
            if (!role.empty()) {
                cout << "Добро пожаловать, " << username << " (" << role << ").\n";
                menu(db, role);
            }
            else {
                cout << "Ошибка\n";
            }
        }
        else if (choice == 2) {
            cout << "Кем является? (сотрудник/клиент/охранник): ";
            cin >> role;
            if (db.addUser(username, password, role)) {
                cout << "Вы зарегистрированы.\n";
            }
            else {
                cout << "Этот пользователь уже зарегистрирован.\n";
            }
        }
    }
}