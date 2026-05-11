#include "Admin.h"

Admin::Admin(string user, string pass) : 
    username(user), password(pass), lastLogin("") {}

bool Admin::authenticate(string user, string pass) const {
    return (user == username && pass == password);
}

void Admin::setLastLogin(string loginTime) {
    lastLogin = loginTime;
}

string Admin::getLastLogin() const {
    return lastLogin;
}

string Admin::getUsername() const {
    return username;
}