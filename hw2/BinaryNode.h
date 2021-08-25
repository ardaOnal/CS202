/*
* Title: Binary Search Trees
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 2
* Description: BinaryNode Header File
*/

#ifndef __BINARYNODE_H
#define __BINARYNODE_H
#include <iostream>
#include <cstddef>
class BinaryNode
{
private:
    BinaryNode();
    BinaryNode(const int& nodeItem, BinaryNode*, BinaryNode*);

    int item;       // data portion
    BinaryNode *leftChildPtr;  // pointer to left child
    BinaryNode *rightChildPtr; // pointer to right child

    friend class BinarySearchTree;
public:
    int getItem();
    BinaryNode* getLeftChild();
    BinaryNode* getRightChild();
    void setItem( int);
    void setLeftChild( BinaryNode*);
    void setRightChild( BinaryNode*);

};
#endif
