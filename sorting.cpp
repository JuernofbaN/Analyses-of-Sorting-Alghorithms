/*
* Title: Algorithm Efficiency and Sorting
* Author: Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 1
* Description: My code creates random arrays and calculate their sorting execution times for merge, quick and insertion sorts.
*/
#include "sorting.h"
#include <iostream>
#include "auxArrayFunctions.h"
#include <ctime>

using namespace std;
void insertionSort(int* arr, int n, int& compCount, int& moveCount) {

    for (int unsorted = 1; unsorted < n; ++unsorted) {
        int nextItem = arr[unsorted];
        moveCount++;
        int loc = unsorted;

        compCount++;
        for (; (loc > 0) && (arr[loc - 1] > nextItem); --loc) {
            compCount++;
            arr[loc] = arr[loc - 1];
            moveCount++;
        }

        arr[loc] = nextItem;
        moveCount++;
    }
}
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}
void partition(int theArray[], int first, int last,
    int& pivotIndex, int& compCount, int& moveCount) {
    // Precondition: theArray[first..last] is an array; first <= last.
    // Postcondition: Partitions theArray[first..last] such that:
    //   S1 = theArray[first..pivotIndex-1] < pivot
    //   theArray[pivotIndex] == pivot
    //   S2 = theArray[pivotIndex+1..last] >= pivot

     // place pivot in theArray[first]

    int pivot = theArray[first]; // copy pivot
    moveCount++;
    // initially, everything but pivot is in unknown
    int lastS1 = first;           // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown

     // move one item at a time until unknown region is empty
    for (; firstUnknown <= last; ++firstUnknown) {
        // Invariant: theArray[first+1..lastS1] < pivot
        //            theArray[lastS1+1..firstUnknown-1] >= pivot
        compCount++;
        // move item from unknown to proper region
        if (theArray[firstUnknown] < pivot) {  	// belongs to S1
           
            ++lastS1;
            swap(theArray[firstUnknown], theArray[lastS1]);
            moveCount = moveCount + 3;
        }	// else belongs to S2
    }
    // place pivot in proper position and mark its location
    swap(theArray[first], theArray[lastS1]);
    moveCount = moveCount + 3;
    pivotIndex = lastS1;
}
void quicksorting(int theArray[], int first, int last, int& compCount, int& moveCount) {
    // Precondition: theArray[first..last] is an array.
    // Postcondition: theArray[first..last] is sorted.

    int pivotIndex = first;

    if (first < last) {
       
        // create the partition: S1, pivot, S2
        partition(theArray, first, last, pivotIndex, compCount, moveCount);

        // sort regions S1 and S2
        quicksorting(theArray, first, pivotIndex - 1, compCount, moveCount);
        quicksorting(theArray, pivotIndex + 1, last, compCount, moveCount);
    }
}
void merge(int theArray[], int first, int mid, const int last, int& compCount, int& moveCount)
{
    const int MAX_SIZE = last;
    int* const tempArray = new int[MAX_SIZE + 1];
    //int tempArray[MAX_SIZE]; // Temporary array
   // Initialize the local indices to indicate the subarrays
    int first1 = first; // Beginning of first subarray
    int last1 = mid; // End of first subarray
    int first2 = mid + 1; // Beginning of second subarray
    int last2 = last; // End of second subarray
    // While both subarrays are not empty, copy the
    // smaller item into the temporary array
    int index = first1; // Next available location in tempArray
    while ((first1 <= last1) && (first2 <= last2))
    {
        // At this point, tempArray[first..index-1] is in order
        if (theArray[first1] <= theArray[first2])
        {
            compCount++;
            tempArray[index] = theArray[first1];
            moveCount++;
            first1++;
        }
        else
        {
            compCount++;
            tempArray[index] = theArray[first2];
            moveCount++;
            first2++;
        } // end if
        index++;
    } // end while
   // Finish off the first subarray, if necessary
    while (first1 <= last1)
    {
        // At this point, tempArray[first..index-1] is in order
        tempArray[index] = theArray[first1];
        moveCount++;
        first1++;
        index++;
    } // end while
   // Finish off the second subarray, if necessary
    while (first2 <= last2)
    {
        // At this point, tempArray[first..index-1] is in order
        tempArray[index] = theArray[first2];
        moveCount++;
        first2++;
        index++;
    } // end for
   // Copy the result back into the original array
    for (index = first; index <= last; index++) {
        theArray[index] = tempArray[index];
        moveCount++;
    }

    delete[] tempArray;
} // end merge 
void mergeSortAlg(int theArray[], int first, int last, int& compCount, int& moveCount)
{
    if (first < last)
    {
        // Sort each half
        int mid = first + (last - first) / 2; // Index of midpoint
        // Sort left half theArray[first..mid]
        mergeSortAlg(theArray, first, mid, compCount, moveCount);
        // Sort right half theArray[mid+1..last]
        mergeSortAlg(theArray, mid + 1, last, compCount, moveCount);
        // Merge the two halves
        merge(theArray, first, mid, last, compCount, moveCount);
    } // end if
} // end mergeSort 
void mergeSort(int* arr, int size, int& compCount, int& moveCount) {
    mergeSortAlg(arr, 0, size - 1, compCount, moveCount);
}
void quickSort(int* arr, int size, int& compCount, int& moveCount) {
    quicksorting(arr, 0, size - 1, compCount, moveCount);
}

void performanceAnalysis() {
    int* arr1;
    int* arr2;
    int* arr3;
    int size5 = 5000;
    int compCount = 0;
    int moveCount = 0;
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOO--------NEARLY SORTED-------------------OOOOOOOOOOOOOOOOOOOOOOOO" << endl;

    for (int i = 0; i < 6; i++) {
        //createRandomArrays(arr1, arr2, arr3, size5);
        createNearlySortedArrays(arr1, arr2, arr3, size5, 10);
        moveCount = 0;
        compCount = 0;
        clock_t startTime = 0;
        double time;

        startTime = clock();
        insertionSort(arr1, size5, compCount, moveCount);        
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Insertion sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;

        startTime = clock();
        mergeSort(arr2, size5, compCount, moveCount);
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Merge sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;

        startTime = clock();
        quickSort(arr1, size5, compCount, moveCount);
        
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Quick sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;
        size5 = size5 + 5000;
        cout << "******************************************************************" << endl;
    }
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOO--------RANDOM SORTED-------------------OOOOOOOOOOOOOOOOOOOOOOOO" << endl;

    size5 = 5000;
    for (int i = 0; i < 6; i++) {
        moveCount = 0;
        compCount = 0;
        //createRandomArrays(arr1, arr2, arr3, size5);
        createRandomArrays(arr1, arr2, arr3, size5);
        clock_t startTime = 0;
        double time;

        startTime = clock();
        insertionSort(arr1, size5, compCount, moveCount);
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Insertion sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;

        startTime = clock();
        mergeSort(arr2, size5, compCount, moveCount);
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Merge sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;

        startTime = clock();
        quickSort(arr1, size5, compCount, moveCount);

        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Quick sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;
        size5 = size5 + 5000;
        cout << "******************************************************************" << endl;
    }
    size5 = 5000;
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOO--------ALREADY SORTED-------------------OOOOOOOOOOOOOOOOOOOOOOOO" << endl;

    for (int i = 0; i < 6; i++) {
        moveCount = 0;
        compCount = 0;
        //createRandomArrays(arr1, arr2, arr3, size5);
        createAlreadySortedArrays(arr1, arr2, arr3, size5);
        moveCount = 0;
        clock_t startTime = 0;
        double time;

        compCount = 0;
        startTime = clock();
        insertionSort(arr1, size5, compCount, moveCount);
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Insertion sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;

        startTime = clock();
        mergeSort(arr2, size5, compCount, moveCount);
        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Merge sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;

        startTime = clock();
        quickSort(arr1, size5, compCount, moveCount);

        time = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        startTime = 0;
        cout << "Quick sort: " << size5 << " elements " << time << " ms" << endl;
        cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl; cout << "        Move Count: " << moveCount << " --- Compare Count: " << compCount << endl;
        moveCount = 0;
        compCount = 0;
        size5 = size5 + 5000;
        cout << "******************************************************************" << endl;
    }

}