/*
* Title: CS202 HW3
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 3
* Description: PrintRequest Object Header File
*/
#ifndef __PRINTREQUEST_H
#define __PRINTREQUEST_H
class PrintRequest
{
public:

    PrintRequest();
    PrintRequest( int, int, int, int);

	int getId() const;
	int getPriority() const;
	int getRequestTime() const;
	int getProcessTime() const;

	void setId(int);
	void setPriority(int);
    void setRequestTime(int);
    void setProcessTime(int);

private:
	int id;
	int priority;
	int requestTime;
	int processTime;
};
#endif
