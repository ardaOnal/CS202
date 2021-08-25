/*
* Title: CS202 HW4
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 4
* Description: List c++ file for hash table with separate chaining
*/

#include "List.h"

#include <cstddef>
#include <iostream>
using namespace std;

List::List(): size(0), head(NULL)
{
}
List::List( const List& aList): size(aList.size)
{
    if ( aList.head == NULL)
        head = NULL;
    else
    {
        head = new ListNode;
        head->item = aList.head->item;
        ListNode* newPtr = head;

        for (ListNode* origPtr = aList.head->next; origPtr != NULL; origPtr = origPtr->next)
        {
            newPtr->next = new ListNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}
List::~List()
{
    while ( !isEmpty())
        remove(1);
}
bool List::isEmpty() const
{
    return size == 0;
}
int List::getLength() const
{
    return size;
}
List::ListNode* List::find( int index) const
{
    if ( ( index < 1) || (index > getLength()))
        return NULL;
    else
    {
        ListNode* cur = head;
        for ( int skip = 1; skip < index; skip++)
            cur = cur->next;
        return cur;
    }
}
bool List::retrieve( int index, int& dataItem) const
{
    if ((index < 1) || (index > getLength()))
        return false;
    ListNode* cur = find(index);
    dataItem = cur->item;

    return true;
}
bool List::insert(int index, int newItem)
{
    int newLength = getLength() + 1;

    if ( (index < 1) || index > newLength)
        return false;
    ListNode* newPtr = new ListNode;
    size = newLength;
    newPtr->item = newItem;

    if ( index == 1)
    {
        newPtr->next = head;
        head = newPtr;
    }
    else
    {
        ListNode* prev = find(index - 1);
        newPtr->next = prev->next;
        prev -> next = newPtr;
    }
    return true;
}
bool List::remove(int index) {

   ListNode* cur;

   if ((index < 1) || (index > getLength()))
      return false;

   size--;
   if (index == 1){
      cur = head;
      head = head->next;
   }
   else{
      ListNode *prev = find(index-1);
      cur = prev->next;
      prev->next = cur->next;
   }
   cur->next = NULL;
   delete cur;
   cur = NULL;

   return true;
}

int List::getIndex(int index) const
{
    for ( int i = 1; i <= getLength(); i++)
    {
        if ( find(i)->item == index)
        {
            return i;
        }
    }
}
bool List::exists(int index) const
{
    for ( int i = 1; i <= getLength(); i++)
    {
        if ( find(i)->item == index)
        {
            return true;
        }
    }
}



