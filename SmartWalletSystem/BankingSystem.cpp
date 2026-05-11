#include "BankingSystem.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

BankingSystem::BankingSystem() : userCount(0), adminLoggedIn(false), transactionCounter(1) {
    users = new User[MAX_USERS];
    
    // Create sample accounts
    createUserAccount(1001, "Rameen Ramzan", "rameen@email.com", "123-4567", 1000.0);
    createUserAccount(1002, "Umama Zubair", "umama@email.com", "987-6543", 1500.0);
    createUserAccount(1003, "John Doe", "john@email.com", "555-1234", 500.0);
}

BankingSystem::~BankingSystem() {
    delete[] users;
}

string BankingSystem::getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    string datetime = to_string(localTime->tm_year + 1900) + "-" +
                     to_string(localTime->tm_mon + 1) + "-" +
                     to_string(localTime->tm_mday) + " " +
                     to_string(localTime->tm_hour) + ":" +
                     to_string(localTime->tm_min) + ":" +
                     to_string(localTime->tm_sec);
    return datetime;
}

string BankingSystem::getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    string date = to_string(localTime->tm_year + 1900) + "-" +
                 to_string(localTime->tm_mon + 1) + "-" +
                 to_string(localTime->tm_mday);
    return date;
}

// FIXED: Added const qualifier
int BankingSystem::findUserIndex(int accountID) const {
    for (int i = 0; i < userCount; i++) {
        if (users[i].getAccountID() == accountID) {
            if (users[i].getIsActive()) {
                return i;
            } else {
                return -1; // Account exists but is inactive
            }
        }
    }
    return -1; // Account not found
}

void BankingSystem::addTransactionToUser(int userIndex, Transaction* newTransaction) {
    users[userIndex].addTransaction(newTransaction);
}

// Admin functions
bool BankingSystem::adminLogin(string username, string password) {
    if (admin.authenticate(username, password)) {
        adminLoggedIn = true;
        admin.setLastLogin(getCurrentDateTime());
        cout << "Admin login successful! Last login: " << admin.getLastLogin() << "\n";
        return true;
    }
    cout << "Invalid admin credentials!\n";
    return false;
}

void BankingSystem::adminLogout() {
    adminLoggedIn = false;
    cout << "Admin logged out successfully!\n";
}

bool BankingSystem::isAdminLoggedIn() const {
    return adminLoggedIn;
}

void BankingSystem::displayAdminDashboard() const {
    if (!adminLoggedIn) {
        cout << "Access denied! Please login as admin.\n";
        return;
    }
    
    cout << "\n=== ADMIN DASHBOARD ===\n";
    cout << "Last Login: " << (admin.getLastLogin().empty() ? "Never" : admin.getLastLogin()) << "\n";
    cout << "System Overview:\n";
    cout << "- Total Users: " << userCount << "\n";
    cout << "- Active Users: " << Report::getActiveUserCount(users, userCount) << "\n";
    cout << "- Total Balance: $" << Report::getTotalSystemBalance(users, userCount) << "\n";
    cout << "- Pending Scheduled Payments: " << getScheduledPaymentCount() << "\n";
    cout << "- Recent Transactions: " << transactionCounter - 1 << "\n";
}

// FIXED: User management with proper duplicate checking
bool BankingSystem::createUserAccount(int accountID, string name, string email, 
                                     string phone, double initialBalance) {
    if (userCount >= MAX_USERS) {
        cout << "Maximum user limit reached!\n";
        return false;
    }
    
    // Check if account ID already exists (active or inactive)
    for (int i = 0; i < userCount; i++) {
        if (users[i].getAccountID() == accountID) {
            cout << "Account ID already exists!\n";
            return false;
        }
    }
    
    users[userCount] = User(accountID, name, email, phone, initialBalance, getCurrentDate());
    userCount++;
    cout << "Account created successfully for " << name << "!\n";
    return true;
}

bool BankingSystem::updateUserAccount(int accountID, string newName, 
                                     string newEmail, string newPhone) {
    int index = findUserIndex(accountID);
    if (index == -1) {
        cout << "Account not found!\n";
        return false;
    }
    
    if (!newName.empty()) users[index].setName(newName);
    if (!newEmail.empty()) users[index].setEmail(newEmail);
    if (!newPhone.empty()) users[index].setPhone(newPhone);
    
    cout << "Account updated successfully!\n";
    return true;
}

bool BankingSystem::deleteUserAccount(int accountID) {
    int index = findUserIndex(accountID);
    if (index == -1) {
        cout << "Account not found!\n";
        return false;
    }
    
    users[index].setIsActive(false);
    cout << "Account deactivated successfully!\n";
    return true;
}

// Transaction operations
bool BankingSystem::deposit(int accountID, double amount) {
    int index = findUserIndex(accountID);
    if (index == -1) {
        cout << "Account not found!\n";
        return false;
    }
    
    if (amount <= 0) {
        cout << "Invalid amount!\n";
        return false;
    }
    
    double newBalance = users[index].getBalance() + amount;
    users[index].setBalance(newBalance);
    
    // Add to transaction history
    Transaction* newTransaction = new Transaction(
        transactionCounter++, "Deposit", amount, getCurrentDate(), 
        "Cash deposit", accountID
    );
    addTransactionToUser(index, newTransaction);
    
    // Push to undo stack
    undoStack.push(accountID, "Deposit", amount);
    
    cout << "Deposit successful! New balance: $" << newBalance << "\n";
    return true;
}

bool BankingSystem::withdraw(int accountID, double amount) {
    int index = findUserIndex(accountID);
    if (index == -1) {
        cout << "Account not found!\n";
        return false;
    }
    
    if (amount <= 0) {
        cout << "Invalid amount!\n";
        return false;
    }
    
    if (users[index].getBalance() < amount) {
        cout << "Insufficient funds!\n";
        return false;
    }
    
    double newBalance = users[index].getBalance() - amount;
    users[index].setBalance(newBalance);
    
    // Add to transaction history
    Transaction* newTransaction = new Transaction(
        transactionCounter++, "Withdrawal", amount, getCurrentDate(), 
        "Cash withdrawal", accountID
    );
    addTransactionToUser(index, newTransaction);
    
    // Push to undo stack
    undoStack.push(accountID, "Withdrawal", amount);
    
    cout << "Withdrawal successful! New balance: $" << newBalance << "\n";
    return true;
}

bool BankingSystem::transfer(int fromAccountID, int toAccountID, double amount) {
    int fromIndex = findUserIndex(fromAccountID);
    int toIndex = findUserIndex(toAccountID);
    
    if (fromIndex == -1 || toIndex == -1) {
        cout << "One or both accounts not found!\n";
        return false;
    }
    
    if (amount <= 0) {
        cout << "Invalid amount!\n";
        return false;
    }
    
    if (users[fromIndex].getBalance() < amount) {
        cout << "Insufficient funds for transfer!\n";
        return false;
    }
    
    double fromNewBalance = users[fromIndex].getBalance() - amount;
    double toNewBalance = users[toIndex].getBalance() + amount;
    
    users[fromIndex].setBalance(fromNewBalance);
    users[toIndex].setBalance(toNewBalance);
    
    // Add to transaction history for both accounts
    Transaction* fromTransaction = new Transaction(
        transactionCounter++, "Transfer", amount, getCurrentDate(), 
        "Transfer to account " + to_string(toAccountID), fromAccountID
    );
    addTransactionToUser(fromIndex, fromTransaction);
    
    Transaction* toTransaction = new Transaction(
        transactionCounter++, "Transfer", amount, getCurrentDate(), 
        "Transfer from account " + to_string(fromAccountID), toAccountID
    );
    addTransactionToUser(toIndex, toTransaction);
    
    // Push to undo stack
    undoStack.push(fromAccountID, "Transfer", amount, toAccountID);
    
    cout << "Transfer successful!\n";
    return true;
}

bool BankingSystem::undoLastTransaction() {
    int accountID, targetAccountID;
    string transactionType;
    double amount;
    
    if (!undoStack.pop(accountID, transactionType, amount, targetAccountID)) {
        cout << "No transactions to undo!\n";
        return false;
    }
    
    int index = findUserIndex(accountID);
    
    if (transactionType == "Deposit") {
        double newBalance = users[index].getBalance() - amount;
        users[index].setBalance(newBalance);
        cout << "Undid deposit of $" << amount << " from account " << accountID << "\n";
    } 
    else if (transactionType == "Withdrawal") {
        double newBalance = users[index].getBalance() + amount;
        users[index].setBalance(newBalance);
        cout << "Undid withdrawal of $" << amount << " from account " << accountID << "\n";
    }
    else if (transactionType == "Transfer") {
        int targetIndex = findUserIndex(targetAccountID);
        double fromNewBalance = users[index].getBalance() + amount;
        double toNewBalance = users[targetIndex].getBalance() - amount;
        
        users[index].setBalance(fromNewBalance);
        users[targetIndex].setBalance(toNewBalance);
        
        cout << "Undid transfer of $" << amount << " from account " << accountID 
             << " to account " << targetAccountID << "\n";
    }
    
    return true;
}

// History and payments
void BankingSystem::displayTransactionHistory(int accountID) const {
    int index = findUserIndex(accountID);
    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }
    users[index].displayTransactionHistory();
}

void BankingSystem::schedulePayment(int fromAccountID, int toAccountID, double amount, 
                                   string scheduledDate, string description) {
    paymentQueue.enqueue(fromAccountID, toAccountID, amount, scheduledDate, description);
    cout << "Payment scheduled successfully for " << scheduledDate << "!\n";
}

void BankingSystem::displayScheduledPayments() const {
    cout << "\n=== Scheduled Payments ===\n";
    paymentQueue.display();
}

void BankingSystem::processScheduledPayments() {
    string today = getCurrentDate();
    cout << "\n=== Processing Scheduled Payments for " << today << " ===\n";
    
    bool processed = false;
    QueueNode* current = paymentQueue.getFront();
    
    while (current != nullptr) {
        if (current->scheduledDate == today) {
            if (transfer(current->fromAccountID, current->toAccountID, current->amount)) {
                cout << "Processed scheduled payment: " << current->description << "\n";
                processed = true;
            }
        }
        current = current->next;
    }
    
    if (!processed) {
        cout << "No scheduled payments for today.\n";
    }
}

// Display and utility
void BankingSystem::displayAllAccounts() const {
    cout << "\n=== All User Accounts ===\n";
    if (userCount == 0) {
        cout << "No accounts found.\n";
        return;
    }
    
    cout << left << setw(10) << "AccountID" << setw(15) << "Name" 
         << setw(20) << "Email" << setw(15) << "Phone" << setw(10) << "Balance\n";
    cout << string(70, '-') << "\n";
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].getIsActive()) {
            users[i].displayInfo();
        }
    }
}

double BankingSystem::getBalance(int accountID) const {
    int index = findUserIndex(accountID);
    if (index == -1) {
        cout << "Account not found!\n";
        return -1;
    }
    return users[index].getBalance();
}

// Report generation
void BankingSystem::generateUserReport() const {
    if (!adminLoggedIn) {
        cout << "Access denied! Please login as admin.\n";
        return;
    }
    Report::generateUserReport(users, userCount);
}

void BankingSystem::generateTransactionReport(string startDate, string endDate) const {
    if (!adminLoggedIn) {
        cout << "Access denied! Please login as admin.\n";
        return;
    }
    Report::generateTransactionReport(users, userCount, startDate, endDate);
}

void BankingSystem::generateFinancialSummary() const {
    if (!adminLoggedIn) {
        cout << "Access denied! Please login as admin.\n";
        return;
    }
    Report::generateFinancialSummary(users, userCount);
}

void BankingSystem::generateUserActivityReport() const {
    if (!adminLoggedIn) {
        cout << "Access denied! Please login as admin.\n";
        return;
    }
    Report::generateUserActivityReport(users, userCount);
}

// Getters for reports
int BankingSystem::getScheduledPaymentCount() const {
    return paymentQueue.getCount();
}