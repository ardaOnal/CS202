/*
* Title: CS202 HW4
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 4
* Description: List header file for hash table with separate chaining
*/

#ifndef __LIST_H
#define __LIST_H

class List
{
private:
    struct ListNode
    {
        int item;
        ListNode* next;
    };

    int size;
    ListNode* head;
    ListNode* find(int index) const;
    //friend class ;
public:
    List();
    List(const List&);
    ~List();

    bool isEmpty() const;
    int getLength() const;
    bool retrieve( int index, int& dataItem) const;
    bool insert(int index, int newItem);
    bool remove(int index);
    int getIndex(int) const;
    bool exists(int) const;

};
#endif
