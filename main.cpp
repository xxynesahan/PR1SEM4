#include "header.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    VaultDatabase db;

    while (true) {
        cout << "1. Войти\n2. Выйти\nВыберите: ";
        int choice;
        cin >> choice;

        if (choice == 2) break;

        string username, password;
        cout << "Имя пользователя: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;
        string role = db.authenticate(username, password);
        if (!role.empty()) {
            cout << "Добро пожаловать, " << username << " (" << role << ")\n";
            if (role == "director") {
                adminMenu(db);
            }
            else {
                userMenu(db, username);
            }
        }
        else {
            cout << "Ошибка аутентификации.\n";
        }
    }

    return 0;
}
