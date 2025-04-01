#include "header.h"

void menu(DataBase& db, string role) {
    while (true) {
        cout << "\nÌåíþ " << role << + "à:" << " \n1.Ïðîñìîòðåòü òåñòû\n2.Âûéòè\nÂûáåðèòå: ";
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
        cout << "1. Âîéòè\n2. Çàðåãèñòðèðîâàòüñÿ\n3. Âûéòè\nÂûáåðèòå: ";
        int choice;
        cin >> choice;
        if (choice == 3)
            break;

        string username, password, role;
        cout << "Èìÿ: ";
        cin >> username;
        cout << "Ïàðîëü: ";
        cin >> password;

        if (choice == 1) {
            role = db.getRole(username, password);
            if (!role.empty()) {
                cout << "Äîáðî ïîæàëîâàòü, " << username << " (" << role << ").\n";
                menu(db, role);
            }
            else {
                cout << "Îøèáêà\n";
            }
        }
        else if (choice == 2) {
            cout << "Êåì ÿâëÿåòñÿ? (ñîòðóäíèê/êëèåíò/îõðàííèê): ";
            cin >> role;
            if (db.addUser(username, password, role)) {
                cout << "Âû çàðåãèñòðèðîâàíû.\n";
            }
            else {
                cout << "Ýòîò ïîëüçîâàòåëü óæå çàðåãèñòðèðîâàí.\n";
            }
        }
    }
}
