/*
* Title: Binary Search Trees
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 2
* Description: BinarySearchTree Header File
*/

#ifndef __BINARYSEARCHTREE_H
#define __BINARYSEARCHTREE_H
#include <iostream>
#include <cstddef>
#include "BinaryNode.h"
class BinarySearchTree
{
private:
    BinaryNode* root;
    int numberOfNodes; // holds the number of nodes for easier implementation
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void destroyTree(BinaryNode*& treePtr);
    bool isEmpty();
    int getHeight();
    int getHeight( BinaryNode*);
    int getNumberOfNodes();
    bool add( const int newEntry);
    bool insertItem(BinaryNode *& treePtr, const int& newItem);
    bool remove( const int anEntry);
    bool deleteItem(BinaryNode*& treePtr, int searchKey);
    void deleteNodeItem(BinaryNode*& nodePtr);
    void processLeftmost(BinaryNode*& nodePtr, int& treeItem);
    bool contains ( const int anEntry);
    bool findItem(BinaryNode *treePtr, int searchKey);
    void preorderTraverse();
    void printPreorderTraverse( BinaryNode* treePtr);
    void inorderTraverse();
    void printInorderTraverse( BinaryNode* treePtr);
    void postorderTraverse();
    void printPostorderTraverse( BinaryNode* treePtr);
    void levelorderTraverse();
    void printLevel(BinaryNode* root, int level);
    int span( const int a, const int b);
    int span( BinaryNode* treePtr, int& , int a, int b);
    void mirror();
    void mirror( BinaryNode* treePtr);
};
#endif
