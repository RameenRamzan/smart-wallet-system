#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using namespace std;

class Admin {
private:
    string username;
    string password;
    string lastLogin;

public:
    Admin(string user = "admin", string pass = "admin123");
    
    bool authenticate(string user, string pass) const;
    void setLastLogin(string loginTime);
    string getLastLogin() const;
    string getUsername() const;
};

#endif