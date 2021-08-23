/*  
* Title: Algorithm Efficiency and Sorting  
* Author: Turan Mert Duran  
* ID: 21601418
* Section: 1  
* Assignment: 1  
* Description: My code creates random arrays and calculate their sorting execution times for merge, quick and insertion sorts.  
*/
#include <iostream>
#include "sorting.h"
#include "auxArrayFunctions.h"
using namespace std;

int main() {
   // performanceAnalysis();
    int arr[] = { 9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7 };
    int compCount = 0;
    int moveCount = 0;

    insertionSort(arr, 16, compCount, moveCount);
    cout <<"Insertion Sort: move count: "<< moveCount << " : comparsion count :" << compCount << endl;

    moveCount = 0;
    compCount = 0;
    int arr0[] = { 9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7 };

    mergeSort(arr0, 16, compCount, moveCount);
    cout << "Merge Sort: move count: " << moveCount << " : comparsion count :" << compCount << endl;

    moveCount = 0;
    compCount = 0;
    int arr1[] = { 9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7 };
    quickSort(arr1, 16, compCount, moveCount);
    cout << "Quick Sort: move count: " << moveCount << " : comparsion count :" << compCount << endl;
}

