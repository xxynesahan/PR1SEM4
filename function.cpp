#include "header.h"

DataBase::DataBase() {
    users.push_back({ "������", "123y", "���������" });
    users.push_back({ "������", "kar2006", "������" });
    users.push_back({ "��������", "vova1", "��������" });

    tests.push_back({ "������", "��� �� ��������� �� ����������", "���������" });
    tests.push_back({ "������ �����", "��� �� �������� ���� ������", "������" });
    tests.push_back({ "������", "��� ������ ��� �������", "��������" });
    tests.push_back({ "������", "��� ��������� ������� ������", "���������" });
    tests.push_back({ "��������", "��� ���������� ������ ���������", "������" });
    tests.push_back({ "���������", "��� ��������� �������� � ��������", "��������" });
    tests.push_back({ "�����", "��� ���������� ������ ������", "���������" });
    tests.push_back({ "���������", "��� ��������� ������� ������", "������" });
    tests.push_back({ "������", "��� ������� �� ��������", "��������" });
}

bool DataBase::addUser(string username, string password, string role) {
    // ���������, ���� �� ��� ����� ������������
    for (const auto& user : users) {
        if (user.username == username) {
            return false;
        }
    }

    // ��������� ������ ������������
    users.push_back({ username, password, role });
    return true;
}

string DataBase::getRole(string username, string password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return user.role;
        }
    }
    return "";
}

vector<Test> DataBase::getTest(string role) {
    vector<Test> result;
    for (const auto& test : tests) {
        if (test.role == role) {
            result.push_back(test);
        }
    }
    return result;
}
