#include "SimpleGUI.h"
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

void SimpleGUI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void SimpleGUI::printHeader(const string& title) {
    ConsoleColor::setColor(CYAN);
    cout << "\n";
    cout << "================================================\n";
    cout << "           " << title << "\n";
    cout << "================================================\n";
    ConsoleColor::reset();
}

void SimpleGUI::printMenuOption(int number, const string& option) {
    ConsoleColor::setColor(WHITE);
    cout << "   " << number << ". ";
    ConsoleColor::setColor(CYAN);
    cout << option << "\n";
    ConsoleColor::reset();
}

void SimpleGUI::printSuccess(const string& message) {
    ConsoleColor::setColor(GREEN);
    cout << "[SUCCESS] " << message << "\n";
    ConsoleColor::reset();
}

void SimpleGUI::printError(const string& message) {
    ConsoleColor::setColor(RED);
    cout << "[ERROR] " << message << "\n";
    ConsoleColor::reset();
}

void SimpleGUI::printInfo(const string& message) {
    ConsoleColor::setColor(BLUE);
    cout << "[INFO] " << message << "\n";
    ConsoleColor::reset();
}

void SimpleGUI::printWarning(const string& message) {
    ConsoleColor::setColor(YELLOW);
    cout << "[WARNING] " << message << "\n";
    ConsoleColor::reset();
}

void SimpleGUI::printTableHeader(const string& header) {
    ConsoleColor::setColor(MAGENTA);
    cout << "\n" << header << "\n";
    cout << string(60, '=') << "\n";
    ConsoleColor::reset();
}

void SimpleGUI::displayWelcomeArt() {
    ConsoleColor::setColor(CYAN);
    cout << R"(

************************************************
          SMART BANKING WALLET SYSTEM
             Developed by Team FAST
          Rameen Ramzan & Umama Zubair
            FAST-NU Karachi Campus
************************************************
    )" << endl;
    ConsoleColor::reset();
}

void SimpleGUI::displayBankArt() {
    ConsoleColor::setColor(BLUE);
    cout << R"(
        +-----------------------+
        |      FAST BANK        |
        +-----------------------+
    )" << endl;
    ConsoleColor::reset();
}

string SimpleGUI::getInput(const string& prompt) {
    string input;
    ConsoleColor::setColor(WHITE);
    cout << "> " << prompt;
    ConsoleColor::setColor(YELLOW);
    getline(cin, input);
    ConsoleColor::reset();
    return input;
}

int SimpleGUI::getChoice(int min, int max) {
    int choice;
    while (true) {
        ConsoleColor::setColor(WHITE);
        cout << "\nEnter your choice [" << min << "-" << max << "]: ";
        ConsoleColor::setColor(YELLOW);
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            printError("Please enter a valid number!");
            continue;
        }
        cin.ignore();
        
        if (choice >= min && choice <= max) {
            return choice;
        }
        printError("Invalid choice! Please try again.");
    }
}

double SimpleGUI::getAmount() {
    double amount;
    while (true) {
        ConsoleColor::setColor(WHITE);
        cout << "Enter amount: $";
        ConsoleColor::setColor(YELLOW);
        
        if (!(cin >> amount)) {
            cin.clear();
            cin.ignore(10000, '\n');
            printError("Please enter a valid amount!");
            continue;
        }
        cin.ignore();
        
        if (amount > 0) {
            return amount;
        }
        printError("Amount must be positive!");
    }
}

SimpleGUI::SimpleGUI() {
    bankingSystem = new BankingSystem();
}

SimpleGUI::~SimpleGUI() {
    delete bankingSystem;
}

void SimpleGUI::handleLoginScreen() {
    clearScreen();
    displayWelcomeArt();
    
    printHeader("ADMIN LOGIN");
    
    int attempts = 0;
    while (attempts < 3) {
        string username = getInput("Username: ");
        string password = getInput("Password: ");
        
        if (bankingSystem->adminLogin(username, password)) {
            printSuccess("Login successful! Welcome to Smart Banking System.");
            return;
        } else {
            attempts++;
            printError("Invalid credentials! Attempts left: " + to_string(3 - attempts));
        }
    }
    
    printError("Too many failed attempts. Exiting system.");
    exit(1);
}

void SimpleGUI::handleMainMenu() {
    while (true) {
        clearScreen();
        displayBankArt();
        printHeader("MAIN MENU");
        
        printMenuOption(1, "User Operations");
        printMenuOption(2, "Admin Dashboard");
        printMenuOption(3, "Reports & Analytics");
        printMenuOption(4, "Logout");
        printMenuOption(0, "Exit System");
        
        int choice = getChoice(0, 4);
        
        switch (choice) {
            case 1: handleUserOperations(); break;
            case 2: handleAdminDashboard(); break;
            case 3: handleReportsMenu(); break;
            case 4: 
                bankingSystem->adminLogout();
                printSuccess("Logged out successfully!");
                return;
            case 0:
                printSuccess("Thank you for using Smart Banking Wallet System!");
                exit(0);
        }
    }
}

void SimpleGUI::handleUserOperations() {
    while (true) {
        clearScreen();
        printHeader("USER OPERATIONS");
        
        printMenuOption(1, "Create User Account");
        printMenuOption(2, "Display All Accounts");
        printMenuOption(3, "Deposit Money");
        printMenuOption(4, "Withdraw Money");
        printMenuOption(5, "Transfer Money");
        printMenuOption(6, "Undo Last Transaction");
        printMenuOption(7, "View Transaction History");
        printMenuOption(8, "Schedule Payment");
        printMenuOption(9, "View Scheduled Payments");
        printMenuOption(10, "Process Scheduled Payments");
        printMenuOption(11, "Update User Account");
        printMenuOption(12, "Delete User Account");
        printMenuOption(13, "Check Balance");
        printMenuOption(0, "Back to Main Menu");
        
        int choice = getChoice(0, 13);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int accID = stoi(getInput("Enter Account ID: "));
                string name = getInput("Enter Name: ");
                string email = getInput("Enter Email: ");
                string phone = getInput("Enter Phone: ");
                double balance = getAmount();
                
                if (bankingSystem->createUserAccount(accID, name, email, phone, balance)) {
                    printSuccess("Account created successfully!");
                }
                break;
            }
            
            case 2:
                bankingSystem->displayAllAccounts();
                break;
                
            case 3: {
                int accID = stoi(getInput("Enter Account ID: "));
                double amount = getAmount();
                bankingSystem->deposit(accID, amount);
                break;
            }
            
            case 4: {
                int accID = stoi(getInput("Enter Account ID: "));
                double amount = getAmount();
                bankingSystem->withdraw(accID, amount);
                break;
            }
            
            case 5: {
                int fromAcc = stoi(getInput("Enter From Account ID: "));
                int toAcc = stoi(getInput("Enter To Account ID: "));
                double amount = getAmount();
                bankingSystem->transfer(fromAcc, toAcc, amount);
                break;
            }
            
            case 6:
                bankingSystem->undoLastTransaction();
                break;
                
            case 7: {
                int accID = stoi(getInput("Enter Account ID: "));
                bankingSystem->displayTransactionHistory(accID);
                break;
            }
            
            case 8: {
                int fromAcc = stoi(getInput("Enter From Account ID: "));
                int toAcc = stoi(getInput("Enter To Account ID: "));
                double amount = getAmount();
                string date = getInput("Enter Scheduled Date (YYYY-MM-DD): ");
                string desc = getInput("Enter Description: ");
                bankingSystem->schedulePayment(fromAcc, toAcc, amount, date, desc);
                break;
            }
            
            case 9:
                bankingSystem->displayScheduledPayments();
                break;
                
            case 10:
                bankingSystem->processScheduledPayments();
                break;
                
            case 11: {
                int accID = stoi(getInput("Enter Account ID to update: "));
                string name = getInput("Enter New Name (press enter to skip): ");
                string email = getInput("Enter New Email (press enter to skip): ");
                string phone = getInput("Enter New Phone (press enter to skip): ");
                bankingSystem->updateUserAccount(accID, name, email, phone);
                break;
            }
            
            case 12: {
                int accID = stoi(getInput("Enter Account ID to delete: "));
                bankingSystem->deleteUserAccount(accID);
                break;
            }
            
            case 13: {
                int accID = stoi(getInput("Enter Account ID: "));
                double balance = bankingSystem->getBalance(accID);
                if (balance != -1) {
                    printInfo("Current Balance: $" + to_string(balance));
                }
                break;
            }
        }
        
        cout << "\n";
        printInfo("Press Enter to continue...");
        cin.get();
    }
}

void SimpleGUI::handleAdminDashboard() {
    clearScreen();
    bankingSystem->displayAdminDashboard();
    
    cout << "\n";
    printInfo("Press Enter to continue...");
    cin.get();
}

void SimpleGUI::handleReportsMenu() {
    while (true) {
        clearScreen();
        printHeader("REPORTS & ANALYTICS");
        
        printMenuOption(1, "User Accounts Report");
        printMenuOption(2, "Transaction Report");
        printMenuOption(3, "Financial Summary");
        printMenuOption(4, "User Activity Report");
        printMenuOption(0, "Back to Main Menu");
        
        int choice = getChoice(0, 4);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                bankingSystem->generateUserReport();
                break;
                
            case 2: {
                string startDate = getInput("Enter Start Date (YYYY-MM-DD) or press enter for all: ");
                string endDate = getInput("Enter End Date (YYYY-MM-DD) or press enter for all: ");
                bankingSystem->generateTransactionReport(startDate, endDate);
                break;
            }
                
            case 3:
                bankingSystem->generateFinancialSummary();
                break;
                
            case 4:
                bankingSystem->generateUserActivityReport();
                break;
        }
        
        cout << "\n";
        printInfo("Press Enter to continue...");
        cin.get();
    }
}

void SimpleGUI::run() {
    handleLoginScreen();
    handleMainMenu();
}