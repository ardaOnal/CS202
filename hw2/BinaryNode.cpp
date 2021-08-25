/*
* Title: Binary Search Trees
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 2
* Description: BinaryNode Cpp File
*/
#include "BinaryNode.h"

BinaryNode::BinaryNode()
{
    item = 0; // item is zero as default
    leftChildPtr = NULL; // right and left pointers are null
    rightChildPtr = NULL;
}

BinaryNode::BinaryNode(const int& nodeItem, BinaryNode* left, BinaryNode* right)
{
    item = nodeItem;
    leftChildPtr = left;
    rightChildPtr = right;
}
int BinaryNode::getItem()
{
    return item;
}
BinaryNode* BinaryNode::getLeftChild()
{
    return leftChildPtr;
}
BinaryNode* BinaryNode::getRightChild()
{
    return rightChildPtr;
}
void BinaryNode::setItem( int nodeItem)
{
    item = nodeItem;
}
void BinaryNode::setLeftChild( BinaryNode* left)
{
    leftChildPtr = left;
}
void BinaryNode::setRightChild( BinaryNode* right)
{
    rightChildPtr = right;
}
