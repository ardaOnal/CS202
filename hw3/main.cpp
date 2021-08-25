/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: main function
*/

using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "PriorityQueue.h"
#include "simulator.h"
int main(int argc, char* argv[])
{
        string filename = argv[1];
        //string filename = "TEST.txt";
        stringstream ss;
        ss << argv[2];
        double avgwaitingtime;
        ss >> avgwaitingtime;


        int requestNumber;
        int number;
        int count = 0;
        int index = 0;
        int id;
        int priority;
        int requestTime;
        int processTime;
        PrintRequest* requests;


        ifstream inputFile;

        inputFile.open(filename.c_str(),ios_base::in);

        if ( inputFile >> number)
            requestNumber = number;

        requests = new PrintRequest[requestNumber];

        // Read the input request
        while ( inputFile >> number)
        {
            if ( count == 0)
            {
                id = number;
                count++;
            }
            else if ( count == 1)
            {
               priority = number;
               count++;
            }
            else if ( count == 2)
            {
               requestTime = number;
               count++;
            }
            else if ( count == 3)
            {
               processTime = number;
               count = 0;

               PrintRequest p(id,priority,requestTime,processTime); // Initialize the object with read values
               requests[index] = p; // and store it in an array that will be used for passing to the function
               index++;
            }
        }

        //double avgwaitingtime = 10;
        inputFile.close();
        simulator s;
        s.estimateMinPrinter(requests,requestNumber,avgwaitingtime);

    return 0;
}

