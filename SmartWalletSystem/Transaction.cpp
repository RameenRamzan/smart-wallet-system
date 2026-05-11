#include "Transaction.h"
#include <iostream>
#include <iomanip>
using namespace std;

Transaction::Transaction(int id, string t, double a, string d, string desc, int accID) :
    transactionID(id), type(t), amount(a), date(d), description(desc), accountID(accID), next(nullptr) {}

// Getters
int Transaction::getTransactionID() const { return transactionID; }
string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
string Transaction::getDate() const { return date; }
string Transaction::getDescription() const { return description; }
int Transaction::getAccountID() const { return accountID; }
Transaction* Transaction::getNext() const { return next; }

// Setters
void Transaction::setNext(Transaction* nextTransaction) {
    next = nextTransaction;
}

void Transaction::display() const {
    cout << left << setw(12) << transactionID 
         << setw(10) << type 
         << setw(10) << amount 
         << setw(12) << date 
         << description << "\n";
}