/*
* Title: CS202 HW4
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 4
* Description: Queue class that will be used for searching neighbors
*/
#include <string>
using namespace std;

typedef string QueueItemType;

// TAKEN FROM CS201 SLIDE SET 11 © 2005 Pearson Addison-Wesley.
class Queue{
public:
    Queue();                     // default constructor
    //Queue(const Queue& Q);       // copy constructor
    ~Queue();                    // destructor

    // Queue operations:
    bool isEmpty() const;
    bool enqueue(QueueItemType newItem);
    bool dequeue();
    bool dequeue(QueueItemType& queueFront);
    bool getFront(QueueItemType& queueFront) const;

private:
    // The queue is implemented as a linked list with one external
    // pointer to the front of the queue and a second external
    // pointer to the back of the queue.

    struct QueueNode{
        QueueItemType  item;
        QueueNode*     next;
    };
    QueueNode* backPtr;
    QueueNode* frontPtr;
};

