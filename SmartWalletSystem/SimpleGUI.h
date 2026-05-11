#ifndef SIMPLEGUI_H
#define SIMPLEGUI_H

#include "BankingSystem.h"
#include "colors.h"
#include <string>
#include <iostream>
using namespace std;

class SimpleGUI {
private:
    BankingSystem* bankingSystem;
    
    void clearScreen();
    void printHeader(const string& title);
    void printMenuOption(int number, const string& option);
    void printSuccess(const string& message);
    void printError(const string& message);
    void printInfo(const string& message);
    void printWarning(const string& message);
    void printTableHeader(const string& header);
    
    string getInput(const string& prompt);
    int getChoice(int min, int max);
    double getAmount();
    
    // Screen handlers
    void handleLoginScreen();
    void handleMainMenu();
    void handleUserOperations();
    void handleAdminDashboard();
    void handleReportsMenu();
    
    // ASCII Art
    void displayWelcomeArt();
    void displayBankArt();

public:
    SimpleGUI();
    ~SimpleGUI();
    void run();
};

#endif