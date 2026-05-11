#include "Queue.h"
#include <iostream>
#include <iomanip>
using namespace std;

QueueNode::QueueNode(int from, int to, double amt, string date, string desc) :
    fromAccountID(from), toAccountID(to), amount(amt), scheduledDate(date), 
    description(desc), next(nullptr) {}

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        int from, to;
        double amount;
        string date, desc;
        dequeue(from, to, amount, date, desc);
    }
}

void Queue::enqueue(int fromAccountID, int toAccountID, double amount, 
                    string scheduledDate, string description) {
    QueueNode* newNode = new QueueNode(fromAccountID, toAccountID, amount, scheduledDate, description);
    
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

bool Queue::dequeue(int& fromAccountID, int& toAccountID, double& amount, 
                    string& scheduledDate, string& description) {
    if (isEmpty()) {
        return false;
    }
    
    QueueNode* temp = front;
    fromAccountID = temp->fromAccountID;
    toAccountID = temp->toAccountID;
    amount = temp->amount;
    scheduledDate = temp->scheduledDate;
    description = temp->description;
    
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    return true;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::display() const {
    if (isEmpty()) {
        cout << "No scheduled payments.\n";
        return;
    }
    
    QueueNode* current = front;
    while (current != nullptr) {
        cout << "From: " << current->fromAccountID << " | To: " << current->toAccountID 
             << " | Amount: $" << current->amount << " | Date: " << current->scheduledDate 
             << " | Description: " << current->description << "\n";
        current = current->next;
    }
}

int Queue::getCount() const {
    int count = 0;
    QueueNode* current = front;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

QueueNode* Queue::getFront() const {
    return front;
}