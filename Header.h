#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <Windows.h>

using namespace std;

struct User {
    string username;
    string password;
    string role;
    bool hasVaultAccess;
};

struct AccessAttempt {
    string username;
    string timestamp;
    bool successful;
};

class SimpleDB {
    const string USERS_FILE = "users.db";
    const string LOGS_FILE = "access_logs.db";

public:
    vector<User> loadUsers();
    bool saveUsers(const vector<User>& users);
    vector<AccessAttempt> loadAccessLogs();
    bool saveAccessLog(const AccessAttempt& log);
};

class VaultDatabase {
    SimpleDB db;
    vector<User> users;
    vector<AccessAttempt> accessLogs;

    void loadData();

public:
    VaultDatabase();
    bool addUser(string username, string password, string role, bool hasAccess);
    string authenticate(string username, string password);
    bool attemptVaultAccess(string username);
    void logAccessAttempt(string username, bool success);
    void showAccessLogs();
    vector<User> getUsersWithAccess();
    bool removeUser(const string& username);
};

void adminMenu(VaultDatabase& db);
void userMenu(VaultDatabase& db, string username);
