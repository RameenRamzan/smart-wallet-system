#include "Report.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Report::generateUserReport(User* users, int userCount) {
    cout << "\n=== USER ACCOUNTS REPORT ===\n";
    cout << left << setw(10) << "AccountID" << setw(15) << "Name" 
         << setw(20) << "Email" << setw(15) << "Phone" << setw(10) << "Balance" 
         << setw(12) << "Join Date" << setw(8) << "Status\n";
    cout << string(100, '-') << "\n";
    
    for (int i = 0; i < userCount; i++) {
        users[i].displayInfo();
    }
}

void Report::generateTransactionReport(User* users, int userCount, 
                                      string startDate, string endDate) {
    cout << "\n=== TRANSACTION REPORT ===\n";
    if (startDate.empty()) startDate = "0000-00-00";
    if (endDate.empty()) endDate = "9999-99-99";
    
    cout << "Period: " << startDate << " to " << endDate << "\n\n";
    
    bool found = false;
    for (int i = 0; i < userCount; i++) {
        Transaction* current = users[i].getTransactionHistory();
        while (current != nullptr) {
            if (current->getDate() >= startDate && current->getDate() <= endDate) {
                if (!found) {
                    cout << left << setw(12) << "TransID" << setw(10) << "Account" 
                         << setw(12) << "Type" << setw(10) << "Amount" 
                         << setw(12) << "Date" << "Description\n";
                    cout << string(70, '-') << "\n";
                    found = true;
                }
                current->display();
            }
            current = current->getNext();
        }
    }
    
    if (!found) {
        cout << "No transactions found in the specified period.\n";
    }
}

void Report::generateFinancialSummary(User* users, int userCount) {
    cout << "\n=== FINANCIAL SUMMARY REPORT ===\n";
    
    double totalDeposits = 0, totalWithdrawals = 0, totalTransfers = 0;
    int depositCount = 0, withdrawalCount = 0, transferCount = 0;
    
    for (int i = 0; i < userCount; i++) {
        Transaction* current = users[i].getTransactionHistory();
        while (current != nullptr) {
            if (current->getType() == "Deposit") {
                totalDeposits += current->getAmount();
                depositCount++;
            } else if (current->getType() == "Withdrawal") {
                totalWithdrawals += current->getAmount();
                withdrawalCount++;
            } else if (current->getType() == "Transfer") {
                totalTransfers += current->getAmount();
                transferCount++;
            }
            current = current->getNext();
        }
    }
    
    cout << "Total Deposits: $" << totalDeposits << " (" << depositCount << " transactions)\n";
    cout << "Total Withdrawals: $" << totalWithdrawals << " (" << withdrawalCount << " transactions)\n";
    cout << "Total Transfers: $" << totalTransfers << " (" << transferCount << " transactions)\n";
    cout << "Net Flow: $" << (totalDeposits - totalWithdrawals) << "\n";
    cout << "System Total Balance: $" << getTotalSystemBalance(users, userCount) << "\n";
}

void Report::generateUserActivityReport(User* users, int userCount) {
    cout << "\n=== USER ACTIVITY REPORT ===\n";
    cout << left << setw(10) << "AccountID" << setw(15) << "Name" 
         << setw(10) << "Balance" << setw(8) << "Transactions" 
         << setw(12) << "Last Active" << setw(10) << "Status\n";
    cout << string(75, '-') << "\n";
    
    for (int i = 0; i < userCount; i++) {
        int transactionCount = users[i].getTransactionCount();
        string lastActive = users[i].getLastActivityDate();
        
        cout << left << setw(10) << users[i].getAccountID() 
             << setw(15) << users[i].getName() 
             << setw(10) << users[i].getBalance() 
             << setw(8) << transactionCount 
             << setw(12) << (lastActive.empty() ? "Never" : lastActive)
             << setw(10) << (users[i].getIsActive() ? "Active" : "Inactive") << "\n";
    }
}

int Report::getActiveUserCount(User* users, int userCount) {
    int count = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].getIsActive()) count++;
    }
    return count;
}

double Report::getTotalSystemBalance(User* users, int userCount) {
    double total = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].getIsActive()) {
            total += users[i].getBalance();
        }
    }
    return total;
}