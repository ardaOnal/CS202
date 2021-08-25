/*
* Title: CS202 HW4
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 4
* Description: WordNetwork header file
*/

#ifndef __WORDNETWORK_H
#define __WORDNETWORK_H

#include "List.h"
#include <string>
using namespace std;

class WordNetwork {
public :
    WordNetwork(const string vertexFile, const string edgeFile);
    ~WordNetwork();
    void listNeighbors(const string word);
    void listNeighbors(const string word, const int distance);
    void listConnectedComponents();
    void findShortestPath(const string word1, const string word2);
    void dfsConnectedComponets( int index, bool*& visited);

private :
    int hash(const string &key, int tableSize);

    int MAX_TABLE_SIZE;
    List* hashTable;
    bool** adjacencyMatrix;
    string* words;
    int wordCount;

// define your data members here
// define private member functions here , if any
// you MUST use the adjacency matrix representation
};
#endif
