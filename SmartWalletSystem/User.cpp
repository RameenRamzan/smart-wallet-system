#include "User.h"
#include <iostream>
#include <iomanip>
using namespace std;

User::User() : accountID(0), name(""), email(""), phone(""), balance(0.0), 
               joinDate(""), isActive(true), transactionHistory(nullptr) {}

User::User(int id, string n, string e, string p, double bal, string jDate) : 
    accountID(id), name(n), email(e), phone(p), balance(bal), 
    joinDate(jDate), isActive(true), transactionHistory(nullptr) {}

// Getters
int User::getAccountID() const { return accountID; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }
double User::getBalance() const { return balance; }
string User::getJoinDate() const { return joinDate; }
bool User::getIsActive() const { return isActive; }
Transaction* User::getTransactionHistory() const { return transactionHistory; }

// Setters
void User::setName(string newName) { name = newName; }
void User::setEmail(string newEmail) { email = newEmail; }
void User::setPhone(string newPhone) { phone = newPhone; }
void User::setBalance(double newBalance) { balance = newBalance; }
void User::setIsActive(bool active) { isActive = active; }

void User::addTransaction(Transaction* newTransaction) {
    if (transactionHistory == nullptr) {
        transactionHistory = newTransaction;
    } else {
        Transaction* current = transactionHistory;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newTransaction);
    }
}

int User::getTransactionCount() const {
    int count = 0;
    Transaction* current = transactionHistory;
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }
    return count;
}

string User::getLastActivityDate() const {
    Transaction* current = transactionHistory;
    string lastDate = "";
    while (current != nullptr) {
        if (current->getDate() > lastDate) {
            lastDate = current->getDate();
        }
        current = current->getNext();
    }
    return lastDate;
}

void User::displayInfo() const {
    cout << left << setw(10) << accountID 
         << setw(15) << name 
         << setw(20) << email 
         << setw(15) << phone 
         << setw(10) << balance 
         << setw(12) << joinDate 
         << setw(8) << (isActive ? "Active" : "Inactive") << "\n";
}

void User::displayTransactionHistory() const {
    cout << "\n=== Transaction History for Account " << accountID << " ===\n";
    cout << "Account Holder: " << name << "\n";
    cout << "Current Balance: $" << balance << "\n\n";
    
    Transaction* current = transactionHistory;
    if (current == nullptr) {
        cout << "No transactions found.\n";
        return;
    }
    
    cout << left << setw(12) << "Transaction" << setw(10) << "Type" 
         << setw(10) << "Amount" << setw(12) << "Date" << "Description\n";
    cout << string(60, '-') << "\n";
    
    while (current != nullptr) {
        current->display();
        current = current->getNext();
    }
}