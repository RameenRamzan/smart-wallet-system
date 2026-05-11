#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include "User.h"
#include "Stack.h"
#include "Queue.h"
#include "Admin.h"
#include "Report.h"
#include <string>
using namespace std;

class BankingSystem {
private:
    static const int MAX_USERS = 100;
    User* users;
    int userCount;
    Stack undoStack;
    Queue paymentQueue;
    Admin admin;
    bool adminLoggedIn;
    int transactionCounter;
    
    // Utility functions
    string getCurrentDateTime();
    string getCurrentDate();
    int findUserIndex(int accountID) const;  // ADDED const here
    void addTransactionToUser(int userIndex, Transaction* newTransaction);
    
public:
    BankingSystem();
    ~BankingSystem();
    
    // Admin functions
    bool adminLogin(string username, string password);
    void adminLogout();
    bool isAdminLoggedIn() const;
    void displayAdminDashboard() const;
    
    // User management
    bool createUserAccount(int accountID, string name, string email, 
                          string phone, double initialBalance = 0.0);
    bool updateUserAccount(int accountID, string newName = "", 
                          string newEmail = "", string newPhone = "");
    bool deleteUserAccount(int accountID);
    
    // Transaction operations
    bool deposit(int accountID, double amount);
    bool withdraw(int accountID, double amount);
    bool transfer(int fromAccountID, int toAccountID, double amount);
    bool undoLastTransaction();
    
    // History and payments
    void displayTransactionHistory(int accountID) const;
    void schedulePayment(int fromAccountID, int toAccountID, double amount, 
                        string scheduledDate, string description);
    void displayScheduledPayments() const;
    void processScheduledPayments();
    
    // Display and utility
    void displayAllAccounts() const;
    double getBalance(int accountID) const;
    
    // Report generation
    void generateUserReport() const;
    void generateTransactionReport(string startDate = "", string endDate = "") const;
    void generateFinancialSummary() const;
    void generateUserActivityReport() const;
    
    // Getters for reports
    int getScheduledPaymentCount() const;
};

#endif