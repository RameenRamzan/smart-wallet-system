#include "Stack.h"

StackNode::StackNode(int accID, string transType, double amt, int targetAccID) :
    accountID(accID), transactionType(transType), amount(amt), 
    targetAccountID(targetAccID), next(nullptr) {}

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    clear();
}

void Stack::push(int accountID, string transactionType, double amount, int targetAccountID) {
    StackNode* newNode = new StackNode(accountID, transactionType, amount, targetAccountID);
    newNode->next = top;
    top = newNode;
}

bool Stack::pop(int& accountID, string& transactionType, double& amount, int& targetAccountID) {
    if (isEmpty()) {
        return false;
    }
    
    StackNode* temp = top;
    accountID = temp->accountID;
    transactionType = temp->transactionType;
    amount = temp->amount;
    targetAccountID = temp->targetAccountID;
    
    top = top->next;
    delete temp;
    return true;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::clear() {
    while (!isEmpty()) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}