/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: PriorityQueue cpp file
*/
#include "PriorityQueue.h"
PriorityQueue::PriorityQueue()
{
    h = new Heap();
}

PriorityQueue::PriorityQueue( int size)
{
    h = new Heap(size);
}

PriorityQueue::PriorityQueue( PriorityQueue& copyQueue)
{
    h = new Heap( *(copyQueue.h));
}

PriorityQueue::~PriorityQueue()
{
    delete h;
}

bool PriorityQueue::pqIsEmpty() const {
	return h->heapIsEmpty();
}

void PriorityQueue::pqInsert(const PQItemType& newItem)
{
    h->heapInsert(newItem);
}

void PriorityQueue::pqDelete(PQItemType& priorityItem)
{
    h->heapDelete(priorityItem);
}

void PriorityQueue::printPriorityQueue()
{
    h->heapPrint();
}
