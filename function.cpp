#include "header.h"

DataBase::DataBase() {
    users.push_back({ "Юлиана", "123", "сотрудник" });
    users.push_back({ "Владимир", "45", "охранник" });

    tests.push_back({ "Фишинг", "Как не попасться на мошенников", "сотрудник" });
    tests.push_back({ "Охрана", "Что делать при тревоге", "охранник" });
    tests.push_back({ "Пароли", "Как придумать хороший пароль", "сотрудник" });
    tests.push_back({ "Документы", "Как проверять паспорта и пропуска", "охранник" });
    tests.push_back({ "Обман", "Как распознать хитрые уловки", "сотрудник" });
    tests.push_back({ "Камеры", "Как следить за порядком", "охранник" });
}

bool DataBase::addUser(string username, string password, string role) {
    for (const auto& user : users) {
        if (user.username == username) {
            return false;
        }
    }

    users.push_back({ username, password, role });
    return true;
}

bool DataBase::removeUser(string username) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->username == username) {
            users.erase(it);
            return true;
        }
    }
    return false;
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
