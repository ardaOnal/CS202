/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: Simulator object that calculates the minimum amount of printer needed in a specified maximum average waiting time
*/
#include "simulator.h"
#include <iostream>
using namespace std;

simulator::simulator()
{

}

void simulator::estimateMinPrinter(PrintRequest*& printRequests, int requestNumber, double avgwaitingtime)
{
    int printerNumber = 1;
    int requestCount = 0;
    int proccessedAmount = 0;
    double waitav = 0;
    int* printerUsageArray;
    bool* printerAvailabilityArray; // holds the availability of printers
    int* printerNextAvailableTime;  // holds the next available time of printers
    int* waitingTimeArray; // holds the waiting time of each print request
    int* requestIdArray; // holds the process order of ids
    int* printTimeArray; // holds the print time of each request
    bool testDone = false;
    bool printed = false;

    while ( !testDone)
    {
        // Initialize arrays
        printerUsageArray = new int[requestNumber];
        printerAvailabilityArray = new bool[printerNumber];
        printerNextAvailableTime = new int[printerNumber];
        waitingTimeArray = new int[requestNumber];
        requestIdArray = new int [requestNumber];
        printTimeArray = new int [requestNumber];

        for ( int i = 0; i < requestNumber; i++)
            printerUsageArray[i] = 0;

        for ( int i = 0; i < requestNumber; i++)
            waitingTimeArray[i] = 0;

        for ( int i = 0; i < requestNumber; i++)
            requestIdArray[i] = 0;

        for ( int i = 0; i < requestNumber; i++)
            printTimeArray[i] = 0;

        for ( int i = 0; i < printerNumber; i++)
            printerAvailabilityArray[i] = true; // Every printer is available at the beginning

        for ( int i = 0; i < printerNumber; i++)
            printerNextAvailableTime[i] = 0;


        PrintRequest request;
        PriorityQueue tmp( requestNumber); // Initialize the priority queue

        for ( int time = 1; requestCount < requestNumber; time++)
        {
            for ( int b = proccessedAmount; b < requestNumber; b++)
            {
                // If a new request comes, insert it into the priority queue
                if ( printRequests[b].getRequestTime() <= time)
                {
                    tmp.pqInsert(printRequests[b]);
                    proccessedAmount++;
                }
            }


            //tmp.printPriorityQueue(); // can be used for looking at the queue at each step

            // Update if the printer is now available
            for ( int j = 0; j < printerNumber; j++)
            {
                // Update the availability of printers every minute
                if ( printerNextAvailableTime[j] <= time)
                {
                    printerAvailabilityArray[j] = true;
                    printerNextAvailableTime[j] = 0;
                }

            }

            // find available printer
            for ( int k = 0; k < printerNumber; k++)
            {
                // also works if the printer updating mechanism is here
//                if ( printerNextAvailableTime[k] <= time)
//                {
//                    printerAvailabilityArray[k] = true;
//                    printerNextAvailableTime[k] = 0;
//                }

                // Print the request if there is an available printer
                if ( printerAvailabilityArray[k])
                {
                    if ( !tmp.pqIsEmpty())
                    {
                        tmp.pqDelete(request); // get the request with highest priority from priority queue

                        printerAvailabilityArray[k] = false; // Printer is since it is working on this request occupied
                        printerNextAvailableTime[k] = time + request.getProcessTime(); // Calculate next available time of this printer

                        waitingTimeArray[requestCount] = time - request.getRequestTime(); // Store the waiting time of print
                        requestIdArray[requestCount] = request.getId(); // Store the id of request for printing it later
                        printTimeArray[requestCount] = time; // Store the time of request for printing it later
                        printerUsageArray[requestCount] = k; // Store which printer is used for printing

                        requestCount++;
                        time--; // Stopping the time and breaking and checking the update status of printers
                        break;
                    }
                }
            }
        }

        // Compute wait time average
        for ( int a = 0; a < requestNumber; a++)
            waitav = waitav + waitingTimeArray[a];

        waitav = waitav / requestNumber; // Compute average of waittime

        // maximum average waiting time is found
        if ( waitav < avgwaitingtime)
            testDone = true;

        // If test is done don't delete these array because they are used for printing the simulation
        if ( !testDone)
        {
            delete [] printerUsageArray;
            delete [] waitingTimeArray;
            delete [] requestIdArray;
            delete [] printTimeArray;
            printerNumber++;
            waitav = 0; // reset waitav because we have to it was greater than max wait average
        }

        requestCount = 0;
        proccessedAmount = 0;

        delete [] printerAvailabilityArray;
        delete [] printerNextAvailableTime;
    }

    // Print the simulation
    cout << "Minimum number of printers required: " << printerNumber << endl;
    cout << endl;
    cout << endl;
    cout << "Simulation with " << printerNumber << " printers:" << endl;
    cout << endl;
    cout << endl;

    for ( int n = 0; n < requestNumber; n++)
    {
        cout << "Printer " << printerUsageArray[n] << " prints print request " << requestIdArray[n] << " at minute " << printTimeArray[n]
        << " (wait: " << waitingTimeArray[n] << " mins)" << endl;
    }

    cout << endl;
    cout << endl;
    cout << "Average waiting time: " << waitav << " minutes" << endl;

    // delete arrays to avoid memory leak
    delete [] printerUsageArray;
    delete [] waitingTimeArray;
    delete [] requestIdArray;
    delete [] printTimeArray;
    delete [] printRequests;

}
