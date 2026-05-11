#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
private:
    int transactionID;
    string type;
    double amount;
    string date;
    string description;
    int accountID;
    Transaction* next;

public:
    Transaction(int id, string t, double a, string d, string desc, int accID);
    
    // Getters
    int getTransactionID() const;
    string getType() const;
    double getAmount() const;
    string getDate() const;
    string getDescription() const;
    int getAccountID() const;
    Transaction* getNext() const;
    
    // Setters
    void setNext(Transaction* nextTransaction);
    
    // Display
    void display() const;
};

#endif