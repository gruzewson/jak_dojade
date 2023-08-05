#include "FifoQueue.h"

FifoQueue::FifoQueue() : head(nullptr), tail(nullptr) {}

void FifoQueue::pushback(int x, int y, int distance)
{
    Node* newNode = new Node{ x, y, distance, nullptr };

    if (isEmpty()) 
    {
        head = tail = newNode;
    }
    else 
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void FifoQueue::popback()
{
    if (isEmpty()) 
    {
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;

    if (isEmpty()) 
    {
        tail = nullptr;
    }
}

Node* FifoQueue::first()
{
    return head;
}

int FifoQueue::firstX()
{
    if (isEmpty()) 
    {
        return 0;
    }
    else
        return head->x;
}

int FifoQueue::firstY()
{
    if (isEmpty())
    {
        return 0;
    }
    else
        return head->y;
}

bool FifoQueue::isEmpty()
{
    return head == nullptr;
}

void FifoQueue::clear() 
{
    while (!isEmpty()) 
    {
        popback();
    }
}

FifoQueue::~FifoQueue()
{
    while (isEmpty() == false) 
    {
        popback();
    }
}




