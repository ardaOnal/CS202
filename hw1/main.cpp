#include "sorting.h"
#include <iostream>
using namespace std;
int main()
{
    const int arrsize = 16;
    int* x = new int[arrsize]{12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    int compCount = 0;
    int moveCount = 0;

    sorting sortobject;

    cout << "INITIAL NUMBERS:" << endl;
    sortobject.displayArray(x,arrsize);
    cout << endl;

    cout << "SELECTION SORT:" << endl;
    sortobject.selectionSort(x,arrsize,compCount,moveCount);
    sortobject.displayArray(x,arrsize);
    cout << "Number of key comparisons: " << compCount << endl;
    cout << "Number of data moves: " << moveCount << endl;
    cout << endl;

    delete [] x;

    x = new int[arrsize]{12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    compCount = 0;
    moveCount = 0;
    cout << "MERGE SORT:" << endl;
    sortobject.mergeSort(x,arrsize,compCount,moveCount);
    cout << "Sorted array: ";
    sortobject.displayArray(x,arrsize);
    cout << "Number of key comparisons: " << compCount << endl;
    cout << "Number of data moves: " << moveCount << endl;
    cout << endl;

    delete [] x;

    x = new int[arrsize]{12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    compCount = 0;
    moveCount = 0;
    cout << "QUICK SORT:" << endl;
    sortobject.quickSort(x,arrsize,compCount,moveCount);
    cout << "Sorted array: ";
    sortobject.displayArray(x,arrsize);
    cout << "Number of key comparisons: " << compCount << endl;
    cout << "Number of data moves: " << moveCount << endl;
    cout << endl;

    delete [] x;

    x = new int[arrsize]{12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    cout << "RADIX SORT:" << endl;
    cout << "Sorted array:";
    sortobject.radixSort(x,arrsize);
    sortobject.displayArray(x,arrsize);
    cout << endl;

//    cout << "PERFORMANCE ANALYSIS:" << endl;
//    sortobject.performanceAnalysis();
//    cout << endl;

    delete [] x;
    return 0;
}
