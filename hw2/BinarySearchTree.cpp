/*
* Title: Binary Search Trees
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 2
* Description: BinarySearchTree Header File
*/
#include "BinarySearchTree.h"
using namespace std;
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
    numberOfNodes = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    destroyTree(root);
}

void BinarySearchTree::destroyTree(BinaryNode*& treePtr) {

        // traverses every node and deletes them recursively
		if (treePtr != NULL){
			destroyTree(treePtr->leftChildPtr);
			destroyTree(treePtr->rightChildPtr);
			delete treePtr;
			treePtr = NULL;
		}
}

bool BinarySearchTree::isEmpty()
{
    return root == NULL;
}

int BinarySearchTree::getHeight()
{
    return getHeight( root);
}

int BinarySearchTree::getHeight( BinaryNode* node)
{
    if ( node == NULL)
        return 0;
    else
    {
        int leftHeight;
        int rightHeight;

        // find right and left height
        leftHeight = getHeight( node->leftChildPtr);
        rightHeight = getHeight( node->rightChildPtr);

        // compares the left height and the right height and return by incrementing the greater value
        if ( leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

int BinarySearchTree::getNumberOfNodes()
{
    return numberOfNodes;
}

bool BinarySearchTree::add( const int newEntry)
{
    return insertItem( root, newEntry);
}

// This function is taken from the slides
bool BinarySearchTree::insertItem(BinaryNode*& treePtr,
				const int& newItem) {

		// Position of insertion found; insert after leaf
		if (treePtr == NULL) {
			treePtr = new BinaryNode(newItem, NULL, NULL);
			numberOfNodes++; // Increase the number of nodes property
			return true;
		}
		// Else search for the insertion position
		else if (newItem < treePtr->item)
			insertItem(treePtr->leftChildPtr, newItem);
        else if ( newItem == treePtr->item)
            return false;
		else
			insertItem(treePtr->rightChildPtr, newItem);
}

bool BinarySearchTree::remove( const int anEntry)
{
    return deleteItem(root, anEntry);
}

// This function is taken from the slides
bool BinarySearchTree::deleteItem(BinaryNode*& treePtr, int searchKey){
		if (treePtr == NULL) // Empty tree
			return false;

		// Position of deletion found
		else if (searchKey == treePtr->item)
        {
            deleteNodeItem(treePtr);
            return true;
        }
		// Else search for the deletion position
		else if (searchKey < treePtr->item)
			deleteItem(treePtr->leftChildPtr, searchKey);
		else
			deleteItem(treePtr->rightChildPtr, searchKey);
}
// This function is taken from the slides
void BinarySearchTree::deleteNodeItem(BinaryNode*& nodePtr) {
		BinaryNode* delPtr;
		int replacementItem;


		// (1)  Test for a leaf
		if ( (nodePtr->leftChildPtr == NULL) &&
		     (nodePtr->rightChildPtr == NULL) ) {
			delete nodePtr;
			nodePtr = NULL;
		}


		// (2)  Test for no left child
		else if (nodePtr->leftChildPtr == NULL){
			delPtr = nodePtr;
			nodePtr = nodePtr->rightChildPtr;
			delPtr->rightChildPtr = NULL;
			delete delPtr;
		}

		// (3)  Test for no right child
		else if (nodePtr->rightChildPtr == NULL) {
			delPtr = nodePtr;
			nodePtr = nodePtr->leftChildPtr;
			delPtr->leftChildPtr = NULL;
			delete delPtr;
		}


		// (4)  There are two children:
		//      Retrieve and delete the inorder successor
		else {
			processLeftmost(nodePtr->rightChildPtr, replacementItem);
			nodePtr->item = replacementItem;
		}

}
// This function is taken from the slides
void BinarySearchTree::processLeftmost(BinaryNode*& nodePtr, int& treeItem){

		if (nodePtr->leftChildPtr == NULL) {
			treeItem = nodePtr->item;
			BinaryNode* delPtr = nodePtr;
			nodePtr = nodePtr->rightChildPtr;
			delPtr->rightChildPtr = NULL; // defense
			delete delPtr;
		}
		else
			processLeftmost(nodePtr->leftChildPtr, treeItem);
}

bool BinarySearchTree::contains( const int treeItem)
{
		return findItem(root, treeItem);
}

bool BinarySearchTree::findItem(BinaryNode* treePtr, int searchKey) {

        // proccesses the binary search tree by going to right or left by looking if the item is greater or less than the searchKey
		if (treePtr == NULL)
			return false;
		else if (searchKey == treePtr->item)
			return true;
		else if (searchKey < treePtr->item)
			findItem(treePtr->leftChildPtr, searchKey);
		else
			findItem(treePtr->rightChildPtr, searchKey);
}


void BinarySearchTree::preorderTraverse()
{
    printPreorderTraverse( root);
    cout << endl;
}

void BinarySearchTree::printPreorderTraverse( BinaryNode* treePtr)
{
    if ( treePtr == NULL)
        return;

    // process root,left,right
    cout << treePtr->item << " ";
    printPreorderTraverse( treePtr->leftChildPtr);
    printPreorderTraverse( treePtr->rightChildPtr);
}

void BinarySearchTree::inorderTraverse()
{
    printInorderTraverse( root);
    cout << endl;
}

void BinarySearchTree::printInorderTraverse( BinaryNode* treePtr)
{
    if ( treePtr == NULL)
        return;

    // process left,root,right
    printInorderTraverse( treePtr->leftChildPtr);
    cout << treePtr->item << " ";
    printInorderTraverse( treePtr->rightChildPtr);
}

void BinarySearchTree::postorderTraverse()
{
    printPostorderTraverse( root);
    cout << endl;
}

void BinarySearchTree::printPostorderTraverse( BinaryNode* treePtr)
{
    if ( treePtr == NULL)
        return;

    // process left,right,root
    printPostorderTraverse( treePtr->leftChildPtr);
    printPostorderTraverse( treePtr->rightChildPtr);
    cout << treePtr->item << " ";
}

void BinarySearchTree::levelorderTraverse()
{
    // find the height by the getHeight function
    int height = getHeight();

    // loop that prints every level
    for ( int i = 0; i <= height; i++)
        printLevel( root, i);

    cout << endl;
}

void BinarySearchTree::printLevel(BinaryNode* treePtr, int level)
{
    if ( treePtr == NULL)
        return;
    if ( level == 1) // If the level is one, print the item
        cout << treePtr->item << " ";
    else if ( level > 1)
    {
        // traverse recursively by decrementing the level
        printLevel( treePtr->leftChildPtr, level-1);
        printLevel( treePtr->rightChildPtr, level-1);
    }
}

int BinarySearchTree::span( const int a, const int b)
{
    int count = 0;
    span( root, count, a, b);
    return count;
}
int BinarySearchTree::span( BinaryNode* treePtr, int& value, int a, int b)
{
    if (!treePtr)
			return value;

    // If the item is in between a & b, we increment the count
    if ( treePtr->item >= a && treePtr->item <= b)
         value = value + 1;
    // If item is greater than b, go left. If item is greater than a, go right.
    // This else if part exists so that we do not traverse the entire tree.
    else if (treePtr->item > b)
            return span( treePtr->leftChildPtr, value, a, b);
    else if (treePtr->item < a)
			return span( treePtr->rightChildPtr, value, a, b);

    // Recursive Tree traversal
    span(treePtr->rightChildPtr, value, a, b);
    span(treePtr->leftChildPtr, value, a, b);

}

void BinarySearchTree::mirror()
{
    mirror( root);
}

void BinarySearchTree::mirror( BinaryNode* treePtr)
{
    if ( !treePtr)
        return;

    // Swap the left and right child of the pointer
    BinaryNode* tmp = treePtr->leftChildPtr;
    treePtr->leftChildPtr = treePtr->rightChildPtr;
    treePtr->rightChildPtr = tmp;

    // Recursive Tree traversal
    mirror( treePtr->leftChildPtr);
    mirror( treePtr->rightChildPtr);
}


