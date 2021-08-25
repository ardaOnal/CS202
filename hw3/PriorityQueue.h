/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: Priority Queue Header file
*/
#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H
#include "Heap.h"// ADT heap operations
typedef HeapItemType PQItemType;

class PriorityQueue {
public:
    PriorityQueue();
	PriorityQueue( int);
	PriorityQueue( PriorityQueue&);
    ~PriorityQueue();

	// priority-queue operations:
	bool pqIsEmpty() const;
	void pqInsert(const PQItemType& newItem);
	void pqDelete(PQItemType& priorityItem);
	void printPriorityQueue();

	Heap* h;
};
#endif
