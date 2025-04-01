#include "header.h"

void menu(DataBase& db, string role) {
    while (true) {
        cout << "\n���� " << role << + "�:" << " \n1.����������� �����\n2.�����\n��������: ";
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
        cout << "1. �����\n2. ������������������\n3. �����\n��������: ";
        int choice;
        cin >> choice;
        if (choice == 3)
            break;

        string username, password, role;
        cout << "���: ";
        cin >> username;
        cout << "������: ";
        cin >> password;

        if (choice == 1) {
            role = db.getRole(username, password);
            if (!role.empty()) {
                cout << "����� ����������, " << username << " (" << role << ").\n";
                menu(db, role);
            }
            else {
                cout << "������\n";
            }
        }
        else if (choice == 2) {
            cout << "��� ��������? (���������/������/��������): ";
            cin >> role;
            if (db.addUser(username, password, role)) {
                cout << "�� ����������������.\n";
            }
            else {
                cout << "���� ������������ ��� ���������������.\n";
            }
        }
    }
}