/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: Heap cpp file
*/

#include "Heap.h"
#include <iostream>
using namespace std;

// Default constructor
Heap::Heap() : size(0)
{
    count = 0;
}

Heap::Heap( const int& inputSize)
{
    count = 0;
    size = inputSize;
    items = new HeapItemType[size];
}

Heap::Heap( Heap& copyHeap)
{
    size = copyHeap.size;
    count = copyHeap.size;

    items = new HeapItemType[size];

    for ( int i = 0; i < size; i++)
        items[i] = copyHeap.items[i];
}

Heap::~Heap()
{
    delete [] items;
}

bool Heap::heapIsEmpty() const {
	return (count == 0);
}

void Heap::heapInsert(const HeapItemType& newItem){

    // If the array is full, double the array size.
	if (count >= size)
    {
        size = size*2;
        HeapItemType* temp = new HeapItemType[size];

        for ( int i = 0; i < count; i++)
            temp[i] = items[i];

        delete [] items;
        items = new HeapItemType[size];

        for ( int i = 0; i < count; i++)
            items[i] = temp[i];

        delete [] temp;
    }

	// Place the new item at the end of the heap
	items[count] = newItem;

	// Trickle new item up to its proper position
	int place = count;
	int parent = (place - 1)/2;
	while ( (place > 0) && (items[place].getPriority() > items[parent].getPriority())) {

        HeapItemType temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

		place = parent;
		parent = (place - 1)/2;
	}
 	count++;
}

void Heap::heapPrint()
{
    for ( int i = 0; i < count; i++)
        cout << items[i].getId() << " " << items[i].getPriority() << " " << items[i].getRequestTime() << " " <<  items[i].getProcessTime() << endl;
}

void Heap::heapDelete(HeapItemType& rootItem)
{
	if ( !heapIsEmpty())
	{
        rootItem = items[0];
		items[0] = items[--count];
		heapRebuild(0);
	}

}

void Heap::heapRebuild(int root)
{
	int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < count ) {
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < count) && (items[rightChild].getPriority() >= items[child].getPriority()))
        {
            if ( items[rightChild].getPriority() == items[child].getPriority() && items[rightChild].getRequestTime() < items[child].getRequestTime())
                child = rightChild;
            else if ( items[rightChild].getPriority() != items[child].getPriority())
                child = rightChild;
        }


		if ( (items[root].getPriority() < items[child].getPriority()) ||
      ( (items[root].getPriority() == items[child].getPriority()) && (items[root].getRequestTime() > items[child].getRequestTime())))
        {
            HeapItemType temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            // transform the new subtree into a heap
            heapRebuild(child);
		}
	}
}



