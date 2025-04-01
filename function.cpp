#include "header.h"

DataBase::DataBase() {
    users.push_back({ "Юлиана", "123y", "сотрудник" });
    users.push_back({ "Карина", "kar2006", "клиент" });
    users.push_back({ "Владимир", "vova1", "охранник" });

    tests.push_back({ "Фишинг", "Как не попасться на мошенников", "сотрудник" });
    tests.push_back({ "Защита денег", "Как не потерять свои деньги", "клиент" });
    tests.push_back({ "Охрана", "Что делать при тревоге", "охранник" });
    tests.push_back({ "Пароли", "Как придумать хороший пароль", "сотрудник" });
    tests.push_back({ "Переводы", "Как отправлять деньги безопасно", "клиент" });
    tests.push_back({ "Документы", "Как проверять паспорта и пропуска", "охранник" });
    tests.push_back({ "Обман", "Как распознать хитрые уловки", "сотрудник" });
    tests.push_back({ "Банкоматы", "Как правильно снимать деньги", "клиент" });
    tests.push_back({ "Камеры", "Как следить за порядком", "охранник" });
}

bool DataBase::addUser(string username, string password, string role) {
    // Проверяем, есть ли уже такой пользователь
    for (const auto& user : users) {
        if (user.username == username) {
            return false;
        }
    }

    // Добавляем нового пользователя
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
