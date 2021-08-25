/*
* Title: Sorting and Algorithm Efficiency
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 1
* Description: This is the header file for sorting.cpp which is used in solving question 2 and question 3 of homework 1
*/
#ifndef __SORTING_H
#define __SORTING_H

#include <ctime>

class sorting
{
public:
    void selectionSort(int* arr, const int size, int& compCount, int& moveCount);
    void mergeSort(int* arr, const int size, int& compCount, int& moveCount);
    void quickSort(int* arr, const int size, int& compCount, int& moveCount);
    void radixSort(int* arr, const int size);
    void displayArray(const int *arr, const int size);
    void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
    void createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
    void createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
    void performanceAnalysis();
private:
    void mergesort( int* arr, int first, int last, int& compCount, int& moveCount);
    void merge( int* arr, int first, int mid, int last,  int& compCount, int& moveCount);
    void quicksort(int* arr, int first, int last, int& compCount, int& moveCount);
    void partition(int* theArray, int first, int last, int& pivotIndex, int& compCount, int& moveCount);
    int takeDigit(int number,int index);
    void radixsort(int* arr, const int n, const int d);


};
#endif
