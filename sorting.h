/*
* Title: Algorithm Efficiency and Sorting
* Author: Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 1
* Description: My code creates random arrays and calculate their sorting execution times for merge, quick and insertion sorts.
*/
#pragma once
void insertionSort(int* arr, int size, int& compCount, int& moveCount);
void quickSort(int* arr, int size, int& compCount, int& moveCount);
void mergeSort(int* arr, int size, int& compCount, int& moveCount);
void performanceAnalysis();