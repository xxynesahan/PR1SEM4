#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct User { string username, password, role;};
struct Test { string name, description, role;};

// База данных пользователей
class DataBase {
    vector<User> users;
    vector<Test> tests;;

public:
    DataBase();
    bool addUser(string username, string password, string role);
    string getRole(string username, string password);
    vector<Test> getTest(string role);
};