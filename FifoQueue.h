#pragma once

struct Node
{
    int x, y;
    int distance;
    Node* next;
};

class FifoQueue 
{
private:
    Node* head;
    Node* tail;
public:
    FifoQueue();

    void pushback(int x, int y, int distance);
    void popback();
    Node* first();
    int firstX();
    int firstY();
    bool isEmpty();
    void clear();

    ~FifoQueue();

};


