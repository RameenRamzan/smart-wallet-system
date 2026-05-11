#ifndef USER_H
#define USER_H

#include <string>
#include "Transaction.h"
using namespace std;

class User {
private:
    int accountID;
    string name;
    string email;
    string phone;
    double balance;
    string joinDate;
    bool isActive;
    Transaction* transactionHistory;

public:
    // Constructors
    User();
    User(int id, string n, string e, string p, double bal, string jDate);
    
    // Getters
    int getAccountID() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    double getBalance() const;
    string getJoinDate() const;
    bool getIsActive() const;
    Transaction* getTransactionHistory() const;
    
    // Setters
    void setName(string newName);
    void setEmail(string newEmail);
    void setPhone(string newPhone);
    void setBalance(double newBalance);
    void setIsActive(bool active);
    
    // Transaction management
    void addTransaction(Transaction* newTransaction);
    int getTransactionCount() const;
    string getLastActivityDate() const;
    
    // Display
    void displayInfo() const;
    void displayTransactionHistory() const;
};

#endif