/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: Heap header file to be used for PriorityQueue
*/
#ifndef __HEAP_H
#define __HEAP_H

#include "PrintRequest.h"
typedef PrintRequest HeapItemType;

class Heap
{
    public:
        Heap();				// default constructor
        Heap( const int&);
        Heap( Heap&);
        ~Heap();

        bool heapIsEmpty() const;
        void heapInsert(const HeapItemType& newItem);
        void heapDelete(HeapItemType& rootItem);

        void heapPrint();

        HeapItemType* items;
        int size;	// array of heap items
        int count;

    protected:
        void heapRebuild(int root);		// Converts the semiheap rooted at
                                        // index root into a heap

};
#endif
