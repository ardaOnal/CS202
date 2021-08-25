/*
* Title: CS202 HW4
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 4
* Description: WordNetwork c++ file
*/

#include "WordNetwork.h"
#include "Queue.h"
//#include "Stack.h"
#include <fstream>
#include <iostream>
using namespace std;

WordNetwork::WordNetwork(const string vertexFile, const string edgeFile)
{
    MAX_TABLE_SIZE = 1000; // can change
    hashTable = new List[MAX_TABLE_SIZE]; // Initialize hash table as array of lists

    // Counting word number in this block
    ifstream myfile;
    myfile.open( vertexFile.c_str(), ios_base::in);
    string line;
    wordCount = 0;
    int wordLength = 0;
    int index;
    string word;

    while(myfile.eof() == false)
    {
        getline(myfile,line, '\n');

        if ( line.length() > 0)
            wordCount++; // increment wordCount if a word exists

        if ( wordCount == 1)
            word = line;
    }
    myfile.close();
    words = new string[wordCount]; // Initialize words array
    adjacencyMatrix = new bool*[wordCount]; // Initialize adjacencyMatrix
    for ( int i = 0; i < wordCount; i++)
        adjacencyMatrix[i] = new bool[wordCount];

    for ( int i = 0; i < wordCount; i++)
        for ( int j = 0; j < wordCount; j++)
            adjacencyMatrix[i][j] = false; // Set all elements in adjacencyMatrix to false;

    // find word length
    for ( int i = 0; i < word.size();i++)
    {
        if ( word[i] != 13) // char 13 indicates the end of a word (this is necessary to run it on putty)
            wordLength++;
    }

    // Read the words from vertexFile and create the hash table
    //ifstream myfile2;
    myfile.open( vertexFile.c_str(), ios_base::in);
    line = "";
    int count = 0;
    while(myfile.eof() == false)
    {
        getline(myfile,line);
        if ( line.length() <= 0)
            break;

        // string of words is held however, hash table is used to get the index so that we don't search the array every time
        // hash table only holds indexes and it is array of lists for faster search
        // the while loops in the rest of the code is used for extracting the words wanted from the list of indexes on each a specific list
        // that is mapped with the hash function
        words[count] = line.substr(0,wordLength); // add the word to the words array
        hashTable[hash(words[count],MAX_TABLE_SIZE)].insert(1, count); // insert the index to the hashTable
        count++;
    }
    myfile.close();

    // Create adjacency matrix
    ifstream myfile3;
    myfile3.open( edgeFile.c_str(), ios_base::in);
    line = "";

    while(myfile3.eof() == false )
    {
        line = "";
        string word1 = "";
        string word2 = "";
        getline(myfile3,line);
        if ( line.length() > 0 )
        {
            word1 = line.substr(0,wordLength); // get the first word
            word2 = line.substr(wordLength+1,wordLength); // get the second word
        }
        else
            break;


        // Extract words from the line (does not work on putty)
//        for ( int i = 0; i < line.length(); i++)
//        {
//            if ( line[i] != ',')
//                word1 = word1 + line[i];
//            else
//            {
//                for ( int j = i + 1; j < line.length(); j++)
//                {
//                    if ( line[j] != '\n')
//                        word2 = word2 + line[j];
//
//                    i = line.length() + 1;
//                }
//
//            }
//        }

        int counter1 = 1; // counters are used for retrieving the elements from list in hash tables
        int counter2 = 1;
        int index1; // indexes are in hash table
        int index2;

        // Get the index of first word in adj matrix
        while ( hashTable[hash(word1,MAX_TABLE_SIZE)].retrieve(counter1,index1))
        {
            if ( words[index1].compare(word1) == 0)
                break;
            counter1++;
        }

        // Get the index of second word in adj matrix
        while ( hashTable[hash(word2,MAX_TABLE_SIZE)].retrieve(counter2,index2))
        {
            if ( words[index2].compare(word2) == 0)
                break;
            counter2++;
        }

        // set the adjancencies, since it is undirected we mark both ways as true
        adjacencyMatrix[index1][index2] = true;
        adjacencyMatrix[index2][index1] = true;
    }
    myfile3.close();
}

WordNetwork::~WordNetwork()
{
    delete [] hashTable; // delete hashtable
    delete [] words;     // delete string of words

    // delete the adjacency matrix
    for ( int i = 0; i < wordCount; i++)
        delete [] adjacencyMatrix[i];

    delete [] adjacencyMatrix;
}

void WordNetwork::listNeighbors(const string word)
{
    int count = 1;
    int indexOfWord = 0;
    // Find the index of word in the hash table while loop is needed for search in list that is mapped by hash function
    while ( hashTable[hash( word,MAX_TABLE_SIZE)].retrieve(count, indexOfWord))
    {
        // Word does not equal
        if ( words[indexOfWord].compare( word) != 0)
            count++;
        else // Word is found
        {
            bool hasNeighbor = false; // First we check if it has a neighbor
            for ( int i = 0; i < wordCount; i++)
            {
                if ( adjacencyMatrix[indexOfWord][i]) // if there is any adjacent vertice, it has a neighbor
                {
                    hasNeighbor = true;
                    break; // to make it more efficient
                }
            }

            if ( hasNeighbor)
            {
                cout << "Neighbors of " << word << ":" << endl;

                // Find the neighbors from the adj matrix and print them
                for ( int i = 0; i < wordCount; i++)
                {
                    // Print each neighbor
                    if ( adjacencyMatrix[indexOfWord][i])
                        cout << words[i] << endl;
                }
                cout << endl;
            }
            else // Does not have a neighbor
            {
                cout << "Error: " << word << " does not have any neighbors." << endl;
                cout << endl;
            }
            return;
        }
    }

    // If word is not found we end up here
    cout << "Error: " << word << " does not exits." << endl;
    cout << endl;
}

// I tried to implement this without the ideas on slides. My idea similar to 201 hw4 however, it unfortunately misses some paths
// The main idea is deleting edges so that in the traversal we do not go to the same path over and over again.
// But, it misses some paths because there can be multiple ways to go to a vertice.
//void WordNetwork::listNeighbors(const string word, const int distance)
//{
//    int* path = new int[distance+1];
//    int count = 1;
//    int indexOfWord = 0;
//
//    while ( hashTable[hash( word,MAX_TABLE_SIZE)].retrieve(count, indexOfWord))
//    {
//        if ( words[indexOfWord].compare( word) == 0)
//        {
//            path[0] = indexOfWord;
//            break;
//        }
//        else
//        {
//            count++; // eror bas
//        }
//    }
//
//    int pathCount = 1;
//    int current = path[0];
//
//    // Copy adjacency matrix
//    bool** copyAdjacencyMatrix = new bool*[wordCount];
//    for ( int i = 0; i < wordCount; i++)
//        copyAdjacencyMatrix[i] = new bool[wordCount];
//
//    for ( int i = 0; i < wordCount; i++)
//        for ( int j = 0; j < wordCount; j++)
//            copyAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
//
//    bool adjfound = false;
//    int index0;
//    int index1;
//    int amountcounter = 0;
//    // Main loop
//    while ( pathCount > 0)
//    {
//        if ( pathCount-1 == distance)
//        {
//            amountcounter++;
//            for ( int j = 0; j < pathCount - 1; j++)
//                cout << words[path[j]] << " -> ";
//            cout << words[path[pathCount - 1]] << endl;
//
//            copyAdjacencyMatrix[path[pathCount - 2]][path[pathCount - 1]] = false; // delete last way
//            //copyAdjacencyMatrix[path[pathCount - 1]][path[pathCount - 2]] = false;
//
//            pathCount--;
//            current = path[pathCount-1];
//        }
//
//        adjfound = false;
//        bool isWordInPath = false;
//        for ( int i = 0; i < wordCount; i++)
//        {
//            // If is adjacent
//            if ( copyAdjacencyMatrix[current][i])
//            {
//                for ( int j = 0; j < pathCount; j++)
//                {
//                    if ( path[j] == i)
//                        isWordInPath = true;
//                }
//
//                if ( !isWordInPath)
//                {
//                    copyAdjacencyMatrix[i][current] = false; // avoid going back
//                    index0 = i;
//                    index1 = current;
//
//                    path[pathCount] = i;
//                    current = path[pathCount];
//                    pathCount++;
//                    adjfound = true;
//                    break;
//                }
//            }
//        }
//
//        if ( !adjfound)
//        {
//            if ( pathCount >= 2)
//            {
//                copyAdjacencyMatrix[path[pathCount-2]][path[pathCount-1]] = false; // delete last way
//                //copyAdjacencyMatrix[path[pathCount-1]][path[pathCount-2]] = false;
//                //copyAdjacencyMatrix[path[pathCount-1]][path[pathCount]] = true; // restore connection
//                //copyAdjacencyMatrix[path[pathCount]][path[pathCount-1]] = true;
//                //copyAdjacencyMatrix[index0][index1] = true;
//            }
//            pathCount--;
//            if ( pathCount >= 1)
//            {
//                current = path[pathCount-1];
//            }
//
//        }
//    }
//
//    cout << amountcounter << endl;
//
//    // delete copy matrix
//}

// This function uses the bfs algortihm that is on the slides. We check the depth of an vertice in the traversal
// Like level order traversal and if the level or depth is equal to the distance, we store the word for printing later
void WordNetwork::listNeighbors(const string word, const int distance)
{
    if ( distance <= 0) // If distance is invalid print error messege
    {
        cout << "Error: Distance must be greater than 0." << endl;
        cout << endl;
        return;
    }

    int indexOfWord;
    int count = 1;
    bool* visitedWords = new bool[wordCount]; // holds whether the words are visited or not, indexing is same as adj matrix
    int* distances = new int[wordCount]; // holds the distances of each word
    int* parents = new int[wordCount]; // used for printing the paths
    Queue q; // create Queue
    string currentWord; // string that holds current word

    for ( int i = 0; i < wordCount; i++) // set all elements in visited words to 0 and distances to 0 parents to 0
    {
        visitedWords[i] = false;
        distances[i] = 0;
        parents[i] = 0;
    }


    bool exists = false; // this boolean is used for checking if the words exists or not
    // index of word is found from the hashTable and loop is used for searching the list on specific hash mapping index
    while ( hashTable[hash( word,MAX_TABLE_SIZE)].retrieve(count, indexOfWord))
    {
        if ( words[indexOfWord].compare( word) == 0)
        {
           visitedWords[indexOfWord] = true;
           exists = true;
           break;
        }
        else
            count++;
    }

    if ( !exists) // If word does not exist, print error messege
    {
        cout << "Error: " << word << " does not exits." << endl;
        cout << endl;
        delete [] visitedWords; // deleting the arrays created to avoid memory leak
        delete [] distances;
        delete [] parents;
        return;
    }

    parents[indexOfWord] = -1;

    // enqueue the word
    q.enqueue(word);
    count = 1;

    while ( !q.isEmpty())
    {
        q.dequeue(currentWord); // dequeue the current word
        while ( hashTable[hash( currentWord,MAX_TABLE_SIZE)].retrieve(count, indexOfWord)) // find the word in hash table
        {
            if ( words[indexOfWord].compare( currentWord) != 0)
                count++;
            else // word is found
            {
                for ( int i = 0; i < wordCount; i++)
                {
                    // for each adjacent and unvisited vertice, we do execute the if statement
                    if ( adjacencyMatrix[indexOfWord][i] && !visitedWords[i])
                    {
                        visitedWords[i] = true; // set the word as visited
                        q.enqueue( words[i]);   // enqueue the adjacent unvisited word (words is array string array of words and i is index of it
                                                // in adjacencyMatrix that is held in hashtable

                        parents[i] = indexOfWord;
                        distances[i] = distances[indexOfWord] + 1; // Set the distance of the word as the distance of parent + 1
                                                                // distance also refers to depth in graph or level in a tree
                    }
                }
                break;
            }
        }
        count = 1;
    }

    int counter = 0; // counts the number of words with distance specified

    cout << "Neighbors of " << word << " with distance " << distance << ":" << endl;

    for ( int i = 0; i < wordCount; i++)
    {
        if ( distances[i] == distance)
        {
            List neighbors; // is used for storing the path
            int currentCount = 0;
            int current = i;
            while ( parents[current] != -1) // recursively add the ancestors to a list of printing later
            {                                            // loop ends when the current word is the starting word or the traversal amount passes wordCount
                currentCount++;
                if ( currentCount >= wordCount) // check if the words is connected
                {
                    break;
                }
                neighbors.insert(1,current); // insert the current word to head of list
                current = parents[current]; // current now is the ancestor
            }
            // print the path block
            counter++;
            cout << word << " -> ";
            int indexInList;
            while ( neighbors.retrieve(1,indexInList)) // retrieve item from the path list and print
            {
                if ( neighbors.getLength() == 1) // if printing the last element, dont print arrow
                    cout << words[indexInList];
                else
                    cout << words[indexInList] << " -> ";
                neighbors.remove(1);
            }
            cout << endl;
        }
    }

    if ( counter == 0) // If distance is 0, we print an error messege
    {
        cout << "Error: " << word << " does not have any neighbors." << endl;
    }

    cout << endl;

    delete [] visitedWords; // deleting the arrays created to avoid memory leak
    delete [] distances;
    delete [] parents;
}

// I also tried to do the same function with dfs algorithm on slides however, for some reason it did not work
// The idea is increasing the current distance when we push to the stack and decrease current distance when we pop in stack
// While the traversal, we store the words with distance as specified
// unfortunately i couldn't implement this idea
//void WordNetwork::listNeighbors(const string word, const int distance)
//{
//    Stack s;
//    int count = 1;
//    int indexOfWord = 0;
//    //bool* visitedWords = new bool[wordCount];
//    List output;
//
////    for ( int i = 0; i < wordCount; i++)
////        visitedWords[i] = false;
//
//    while ( hashTable[hash( word,MAX_TABLE_SIZE)].retrieve(count, indexOfWord))
//    {
//        if ( words[indexOfWord].compare( word) == 0)
//        {
//           //visitedWords[indexOfWord] = true;
//           break;
//        }
//        else
//            count++;
//    }
//
//    s.push(indexOfWord);
//    int prevParentIndex = -1;
//    int i = 0;
//
//    while ( !s.isEmpty())
//    {
//        s.getTop(indexOfWord);
//        bool found = false;
//
//        for ( ; i < wordCount; i++)
//        {
//            if ( adjacencyMatrix[indexOfWord][i] && !s.exists(i))
//            {
//                s.push(i);
//                //visitedWords[i] = true; // mark it as visited
//                prevParentIndex = indexOfWord;
//                indexOfWord = i;
//                found = true;
//
//                if ( s.getSize() == distance)
//                {
//                    output.insert(1, i);
//                    //s.pop();
//                }
//                break;
//            }
//        }
//
//        i = 0;
//
//        if ( !found)
//        {
//            int ind;
//            s.pop(); // backtrack
//            s.getTop(ind);
//            i = ind + 1;
//        }
//    }
//
//    int counter = 0;
//    // Output
//    while ( !output.isEmpty())
//    {
//        counter++;
//        output.retrieve(1,indexOfWord);
//        cout << words[indexOfWord] << endl;
//        output.remove(1);
//
//    }
//
//    cout << counter;
//}

// This function uses recursive dfs similar to one in the slides
// It uses helper function named dfsConnectedComponets()
void WordNetwork::listConnectedComponents()
{
    bool* visited = new bool[wordCount]; // visited array
    for ( int i = 0; i < wordCount; i++)
        visited[i] = false; // initialize each of them to false

    int count = 1; // used for counting the connect component amount

    for ( int i = 0; i < wordCount; i++)
    {
//        bool hasUnvisitedAdjacent = false; // check if the word has an unvisited adjacent word
//        for ( int k = 0; k < wordCount; k++)
//            if ( adjacencyMatrix[i][k] && !visited[k])
//                hasUnvisitedAdjacent = true;

        //if ( !visited[i] && hasUnvisitedAdjacent) // if the current word is not visited and it has unvisited adjacent word(s) execute
        if ( !visited[i])
        {
            cout << "Connected component " << count << ":" << endl;
            count++;

            dfsConnectedComponets( i, visited); // recursive call
        }
    }

    delete [] visited; // delete visited array for avoiding memory leak
}

// Finds the shortest path using bft. If the traversal reaches the destination word, it back tracks by going to the parent and prints the path.
void WordNetwork::findShortestPath(const string word1, const string word2)
{
    int indexOfWord;
    int count = 1; // used for traversal in list in hash table
    bool* visitedWords = new bool[wordCount]; // holds the visited status of words
    int* ancestors = new int[wordCount]; // in the traversal, we store the parent or ancestor of each vertice
    Queue q; // queue is used for bft
    string currentWord;

    for ( int i = 0; i < wordCount; i++)
    {
        visitedWords[i] = false; // set the visited status of all words as false
        ancestors[i] = 0;        // set the ancestor of all words to 0
    }

    List neighbors; // holds the neighbors that will be printed

    bool exists = false;
    // Find the index of word1 in the hash table
    while ( hashTable[hash( word1,MAX_TABLE_SIZE)].retrieve(count, indexOfWord))
    {
        if ( words[indexOfWord].compare( word1) == 0)
        {
            exists = true; // the word exists
            visitedWords[indexOfWord] = true; // set the word as visited
            break;
        }
        else
            count++;
    }

    if ( !exists) // If word1 does not exists, exit the function and print error messege
    {
        cout << "Error: " << word1 << " does not exists." << endl;
        cout << endl;
        delete [] ancestors; // delete arrays to avoid memory leak
        delete [] visitedWords;
        return;
    }

    q.enqueue(word1); // enqueue the word
    count = 1; // used for traversal in list in hash table

    while ( !q.isEmpty())
    {
        q.dequeue(currentWord); // dequeue current word

        if ( currentWord.compare(word2) == 0) // If we find word2 (destination word, the traversal ends)
            break; // break the while loop
        while ( hashTable[hash( currentWord,MAX_TABLE_SIZE)].retrieve(count, indexOfWord)) // search the index of current word with hash table
        {
            if ( words[indexOfWord].compare( currentWord) != 0)
                count++;
            else // current word is found in hash table
            {
                for ( int i = 0; i < wordCount; i++) // for each unvisited adjacent word
                {
                    if ( adjacencyMatrix[indexOfWord][i] && !visitedWords[i])
                    {
                        visitedWords[i] = true; // set the word as visited
                        q.enqueue( words[i]); // enqueue the new word

                        ancestors[i] = indexOfWord; // hold the ancestor of word in ancestors array
                    }
                }
                break;
            }
        }
        count = 1; // reset hash table list traversal counter
    }

    count = 1; // reset hash table list traversal counter
    int current;

    exists = false;
    while ( hashTable[hash( word2,MAX_TABLE_SIZE)].retrieve(count, indexOfWord))
    {
        if ( words[indexOfWord].compare( word2) == 0) // word is found
        {
            exists = true; // word exists in graph
            current = indexOfWord;
            break;
        }
        else
            count++;
    }

    if ( !exists) // if words2 does not exist in graph, print error messege
    {
        cout << "Error: " << word2 << " does not exists." << endl;
        cout << endl;
        delete [] ancestors; // delete arrays to avoid memory leak
        delete [] visitedWords;
        return;
    }

    int currentCount = 0;
    bool connected = true;
    while ( words[current].compare( word1) != 0) // recursively add the ancestors to a list of printing later
    {                                            // loop ends when the current word is the starting word or the traversal amount passes wordCount
        currentCount++;
        if ( currentCount >= wordCount) // check if the words is connected
        {
            connected = false;
            break;
        }
        neighbors.insert(1,current); // insert the current word to head of list
        current = ancestors[current]; // current now is the ancestor
    }

    if ( !connected)
        cout << "A path does not exist from " << word1 << " to " << word2 << "." << endl;
    else
    {
        cout << "Shortest path from " << word1 << " to " << word2 << ":" << endl;
        cout << word1 << endl;
        int index;

        while ( !neighbors.isEmpty()) // while the list is not empty
        {
            neighbors.retrieve(1,index); // retrieve the head of list
            cout << words[index] << endl; // print word
            neighbors.remove(1); // remove word from list
        }
    }

    cout << endl;

    delete [] ancestors;
    delete [] visitedWords;
}

// Hash function is taken from slides of CS 202 slide set 8: Graphs
int WordNetwork::hash(const string& key, int tableSize)
{
   int hashVal = 0;

   for (int i = 0; i < key.length(); i++)
	hashVal = 37 * hashVal + key[i];
   hashVal %=tableSize;
   if (hashVal < 0)   /* in case overflows occurs */
	hashVal += tableSize;

   return hashVal;
}

// Used in listing the connected components. Takes an index which indicates the index of word in adj matrix and
// takes the visited status of words as an boolean array as function inputs
// Recursively traverses unvisited adjacent words in dft fashion and prints them
void WordNetwork::dfsConnectedComponets( int index, bool*& visited)
{
    cout << words[index] << endl; // print the word
    visited[index] = true; // set it as visited

    for ( int i = 0; i < wordCount; i++) // traverse the adjacency matrix
    {
        // If adjacent and not visited
        if ( adjacencyMatrix[index][i] && !visited[i]) // if a word is unvisited and adjacent
            dfsConnectedComponets( i, visited); // recursively call by passing i as the new index
    }
}

