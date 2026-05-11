#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

struct StackNode {
    int accountID;
    string transactionType;
    double amount;
    int targetAccountID;
    StackNode* next;
    
    StackNode(int accID, string transType, double amt, int targetAccID = -1);
};

class Stack {
private:
    StackNode* top;

public:
    Stack();
    ~Stack();
    
    void push(int accountID, string transactionType, double amount, int targetAccountID = -1);
    bool pop(int& accountID, string& transactionType, double& amount, int& targetAccountID);
    bool isEmpty() const;
    void clear();
};

#endif