#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

struct QueueNode {
    int fromAccountID;
    int toAccountID;
    double amount;
    string scheduledDate;
    string description;
    QueueNode* next;
    
    QueueNode(int from, int to, double amt, string date, string desc);
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    Queue();
    ~Queue();
    
    void enqueue(int fromAccountID, int toAccountID, double amount, 
                 string scheduledDate, string description);
    bool dequeue(int& fromAccountID, int& toAccountID, double& amount, 
                 string& scheduledDate, string& description);
    bool isEmpty() const;
    void display() const;
    int getCount() const;
    QueueNode* getFront() const;
};

#endif