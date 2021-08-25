/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: PrintRequest Object Cpp File
*/
#include "PrintRequest.h"

// Default Constructor sets every property to zero
PrintRequest::PrintRequest()
{
    id = 0;
	priority = 0;
	requestTime = 0;
	processTime = 0;
}

// Constructor sets every property to input parameters
PrintRequest::PrintRequest( int id, int priorty, int requestTime, int processTime)
{
    this->id = id;
    this->priority = priorty;
    this->requestTime = requestTime;
    this->processTime = processTime;
}

int PrintRequest::getId() const
{
    return id;
}
int PrintRequest::getPriority() const
{
    return priority;
}
int PrintRequest::getRequestTime() const
{
    return requestTime;
}
int PrintRequest::getProcessTime() const
{
    return processTime;
}
void PrintRequest::setId(int id)
{
    this->id = id;
}
void PrintRequest::setPriority(int priority)
{
    this->priority = priority;
}
void PrintRequest::setRequestTime(int requestTime)
{
    this->requestTime = requestTime;
}
void PrintRequest::setProcessTime(int processTime)
{
    this->processTime = processTime;
}
