/*
* Title: Sorting and Algorithm Efficiency
* Author: Arda Onal
* ID: 21903350
* Section: 3
* Assignment: 1
* Description: This file implements the selectionSort, mergeSort, quickSort, radixSort and counts the data comparisons and data moves
*/
#include "sorting.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

void sorting::selectionSort(int* arr, const int size, int& compCount, int& moveCount)
{
    for ( int last = size - 1; last >= 1; last--)
    {
        // Finding the largest element
        int largest = 0;
        for (int currentIndex = 1; currentIndex < last + 1; currentIndex++)
        {
            compCount++;
            if (arr[currentIndex] > arr[largest])
                largest = currentIndex;
        }

        // Swap operation
        int tmp = arr[largest];
        arr[largest] = arr[last];
        arr[last] = tmp;
        moveCount = moveCount + 3;
    }
}
void sorting::mergeSort(int* arr, const int size, int& compCount, int& moveCount)
{
    mergesort(arr,0,size-1,compCount,moveCount);
}
void sorting::quickSort(int* arr, const int size, int& compCount, int& moveCount)
{
    quicksort(arr, 0, size - 1, compCount, moveCount);
}
void sorting::radixSort(int* arr, const int size)
{
    int highestNumber = arr[0];

    for ( int i = 1; i < size; i++)
    {
        if ( arr[i] > highestNumber)
            highestNumber = arr[i];
    }

    int digitNumber = 0;
    while ( highestNumber != 0)
    {
        highestNumber = highestNumber / 10;
        digitNumber++;
    }

    radixsort(arr, size, digitNumber);
}

void sorting::displayArray(const int* arr, const int size)
{
    cout << "[";
    for ( int i = 0; i < size - 1; i++)
        cout << arr[i] << ", ";

    cout << arr[size - 1] << "]" << endl;
}
void sorting::createRandomArrays(int*& arr1, int*& arr2, int *&arr3, int *&arr4, const int size)
{
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];

    for ( int i = 0; i < size; i++)
    {
        arr1[i] = rand();
        arr2[i] = rand();
        arr3[i] = rand();
        arr4[i] = rand();
    }
}
void sorting::createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size)
{
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];

    arr1[0] = rand() + 1;
    arr2[0] = rand() + 1;
    arr3[0] = rand() + 1;
    arr4[0] = rand() + 1;

    for ( int i = 1; i < size; i++)
    {
        arr1[i] = arr1[i - 1] + 1;
        arr2[i] = arr2[i - 1] + 1;
        arr3[i] = arr3[i - 1] + 1;
        arr4[i] = arr4[i - 1] + 1;
    }
}
void sorting::createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size)
{
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];

    arr1[0] = rand() + 100;
    arr2[0] = rand() + 100;
    arr3[0] = rand() + 100;
    arr4[0] = rand() + 100;

    for ( int i = 1; i < size; i++)
    {
        arr1[i] = arr1[i - 1] - 1;
        arr2[i] = arr2[i - 1] - 1;
        arr3[i] = arr3[i - 1] - 1;
        arr4[i] = arr4[i - 1] - 1;
    }
}

void sorting::performanceAnalysis()
{
    int *arr0, *arr1, *arr2, *arr3;

    int size = 6000;
    int compCount = 0;
    int moveCount = 0;
    double duration;

    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Selection Sort (Random Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createRandomArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        selectionSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Selection Sort (Ascending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createAscendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        selectionSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }


    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Selection Sort (Descending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createDescendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        selectionSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Merge Sort (Random Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createRandomArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        mergeSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Merge Sort (Ascending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createAscendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        mergeSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Merge Sort (Descending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createDescendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        mergeSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Quick Sort (Random Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createRandomArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        quickSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Quick Sort (Ascending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createAscendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        quickSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Quick Sort (Descending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createDescendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        quickSort(arr0,size,compCount,moveCount);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Radix Sort (Random Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createRandomArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        radixSort(arr0,size);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Radix Sort (Ascending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "compCount" << setw(20) << "moveCount";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createAscendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        radixSort(arr0,size);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Analysis of Radix Sort (Descending Arrays)" << endl;
    cout << endl;
    cout << left << setw(20) << "Array Size" << setw(20) << "Elapsed Time(ms)" << setw(20) << "" << setw(20) << "";
    size = 6000;

    for ( int i = 0; i < 7; i++)
    {
        createDescendingArrays( arr0,arr1,arr2,arr3,size);

        clock_t startTime = clock();
        radixSort(arr0,size);
        duration = 1000 * double( clock() - startTime) / CLOCKS_PER_SEC;

        cout << left << setw(20) << size << setw(20) << duration << setw(20) << compCount << setw(20) << moveCount;

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        size += 4000;
        compCount = 0;
        moveCount = 0;
    }

}
void sorting::mergesort( int* arr, int first, int last, int& compCount, int& moveCount) {

	if (first < last) {

      int mid = (first + last)/2; 	// index of midpoint

      mergesort(arr, first, mid, compCount, moveCount);

      mergesort(arr, mid+1, last, compCount, moveCount);

      // merge the two halves
      merge(arr, first, mid, last, compCount, moveCount);
   }
}  // end mergesort

void sorting::merge( int* arr, int first, int mid, int last, int& compCount, int& moveCount) {

	int* tempArray; 	// temporary array
	tempArray = new int[30000];

	int first1 = first; 	// beginning of first subarray
    int last1 = mid; 		// end of first subarray
    int first2 = mid + 1;	// beginning of second subarray
    int last2 = last;		// end of second subarray
    int index = first1;     // next available location in tempArray

    for ( ; (first1 <= last1) && (first2 <= last2); ++index) {
      compCount++;
      if (arr[first1] < arr[first2]) {
         tempArray[index] = arr[first1];
         moveCount++;
         ++first1;
      }
      else {
          tempArray[index] = arr[first2];
          moveCount++;
          ++first2;
      }
   }

   // finish off the first subarray, if necessary
   for (; first1 <= last1; ++first1, ++index)
   {
       tempArray[index] = arr[first1];
       moveCount++;
   }


   // finish off the second subarray, if necessary
   for (; first2 <= last2; ++first2, ++index)
   {
       tempArray[index] = arr[first2];
       moveCount++;
   }


   // copy the result back into the original array
   for (index = first; index <= last; ++index)
   {
       arr[index] = tempArray[index];
       moveCount++;
   }

   delete [] tempArray;
}

void sorting::quicksort(int* arr, int first, int last, int& compCount, int& moveCount) {
// Precondition: theArray[first..last] is an array.
// Postcondition: theArray[first..last] is sorted.

    int pivotIndex;

    if (first < last) {

        // create the partition: S1, pivot, S2
        partition(arr, first, last, pivotIndex, compCount, moveCount);

        // sort regions S1 and S2
        quicksort(arr, first, pivotIndex-1, compCount, moveCount);
        quicksort(arr, pivotIndex+1, last, compCount, moveCount);
    }
}

void sorting::partition(int* theArray, int first, int last, int& pivotIndex, int& compCount, int& moveCount) {
   // Precondition: theArray[first..last] is an array; first <= last.
   // Postcondition: Partitions theArray[first..last] such that:
   //   S1 = theArray[first..pivotIndex-1] < pivot
   //   theArray[pivotIndex] == pivot
   //   S2 = theArray[pivotIndex+1..last] >= pivot
   int pivot = theArray[first]; // copy pivot
   moveCount++;
    // initially, everything but pivot is in unknown
   int lastS1 = first;           // index of last item in S1
   int firstUnknown = first + 1; // index of first item in unknown

	// move one item at a time until unknown region is empty
   for (  ; firstUnknown <= last; ++firstUnknown) {
      // Invariant: theArray[first+1..lastS1] < pivot
      //            theArray[lastS1+1..firstUnknown-1] >= pivot

      // move item from unknown to proper region
      compCount++;
      if (theArray[firstUnknown] < pivot) {  	// belongs to S1
		  ++lastS1;
    	  int tmp = theArray[firstUnknown];
    	  theArray[firstUnknown] = theArray[lastS1];
    	  theArray[lastS1] = tmp;
    	  moveCount = moveCount + 3;
      }	// else belongs to S2
   }
   // place pivot in proper position and mark its location
   int tmp = theArray[first];
   theArray[first] = theArray[lastS1];
   theArray[lastS1] = tmp;
   moveCount = moveCount + 3;

   pivotIndex = lastS1;
}

int sorting::takeDigit(int number, int index)
{
    int power = 1;

    for ( int i = 0; i < index - 1; i++)
    {
        power = power * 10;
    }

    number = number / power;
    return number % 10;
}

void sorting::radixsort(int* arr, const int n, const int d)
{
    for ( int j = 1; j <= d; j++)
    {
        int* arr0 = new int[n];
        int* arr1 = new int[n];
        int* arr2 = new int[n];
        int* arr3 = new int[n];
        int* arr4 = new int[n];
        int* arr5 = new int[n];
        int* arr6 = new int[n];
        int* arr7 = new int[n];
        int* arr8 = new int[n];
        int* arr9 = new int[n];
        int counter0 = 0;
        int counter1 = 0;
        int counter2 = 0;
        int counter3 = 0;
        int counter4 = 0;
        int counter5 = 0;
        int counter6 = 0;
        int counter7 = 0;
        int counter8 = 0;
        int counter9 = 0;

        for ( int i = 0; i < n; i++)
        {
            int k = takeDigit(arr[i],j);

            switch(k)
            {
            case 0:
                arr0[counter0] = arr[i];
                counter0++;
                break;
            case 1:
                arr1[counter1] = arr[i];
                counter1++;
                break;
            case 2:
                arr2[counter2] = arr[i];
                counter2++;
                break;
            case 3:
                arr3[counter3] = arr[i];
                counter3++;
                break;
            case 4:
                arr4[counter4] = arr[i];
                counter4++;
                break;
            case 5:
                arr5[counter5] = arr[i];
                counter5++;
                break;
            case 6:
                arr6[counter6] = arr[i];
                counter6++;
                break;
            case 7:
                arr7[counter7] = arr[i];
                counter7++;
                break;
            case 8:
                arr8[counter8] = arr[i];
                counter8++;
                break;
            case 9:
                arr9[counter9] = arr[i];
                counter9++;
                break;
            default: break;
            }
        }

        // counter of the main arr
        int counter = 0;

        for ( int a = 0; a < counter0; a++)
        {
            arr[counter] = arr0[a];
            counter++;
        }

        for ( int a = 0; a < counter1; a++)
        {
            arr[counter] = arr1[a];
            counter++;
        }

        for ( int a = 0; a < counter2; a++)
        {
            arr[counter] = arr2[a];
            counter++;
        }

        for ( int a = 0; a < counter3; a++)
        {
            arr[counter] = arr3[a];
            counter++;
        }

        for ( int a = 0; a < counter4; a++)
        {
            arr[counter] = arr4[a];
            counter++;
        }

        for ( int a = 0; a < counter5; a++)
        {
            arr[counter] = arr5[a];
            counter++;
        }

        for ( int a = 0; a < counter6; a++)
        {
            arr[counter] = arr6[a];
            counter++;
        }

        for ( int a = 0; a < counter7; a++)
        {
            arr[counter] = arr7[a];
            counter++;
        }

        for ( int a = 0; a < counter8; a++)
        {
            arr[counter] = arr8[a];
            counter++;
        }

        for ( int a = 0; a < counter9; a++)
        {
            arr[counter] = arr9[a];
            counter++;
        }

        delete [] arr0;
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
        delete [] arr5;
        delete [] arr6;
        delete [] arr7;
        delete [] arr8;
        delete [] arr9;
    }
}





