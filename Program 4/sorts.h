#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// BubbleSort Function
void BubbleSort(vector<int>& vec, int first, int last) {
    for (int i = first; i < last; i++) { //loops every time a number is sorted
        for (int j = first; j < last - i; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// InsertionSort Function
void InsertionSort(vector<int>& vec, int first, int last) {
    for (int i = first + 1; i <= last; i++) { //loops from element at index 1
        int temp = vec[i];
        int j = i - 1; //previous element
        while (j >= first && vec[j] > temp) { //shift elements to the right position
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = temp;
    }
}

// Merge Function
void merge(vector<int>& vec, int first, int mid, int last) {
    int size = last - first + 1;
    int* tmpArr = new int[size]; //temporary array to hold the sorted values
    int first1 = first;          
    int last1 = mid; 
    int first2 = mid + 1;
    int last2 = last;
    int index = 0; //temporary index

    // Merge Two Subarrays
    while ((first1 <= last1) && (first2 <= last2)) {
        if (vec[first1] < vec[first2]) {
            tmpArr[index] = vec[first1];
            first1++;
        } else {
            tmpArr[index] = vec[first2];
            first2++;
        }
        index++;
    }

    // Copy Remaining Elements from First Subarray
    while (first1 <= last1) {
        tmpArr[index] = vec[first1];
        first1++;
        index++;
    }

    // Copy Remaining Elements from Second Subarray
    while (first2 <= last2) {
        tmpArr[index] = vec[first2];
        first2++;
        index++;
    }

    // Copy Sorted Elements to Original Vector
    for (index = 0; index < size; index++) {
        vec[first + index] = tmpArr[index];
    }

    delete[] tmpArr; //free memory of unused object
}

// MergeSort (recursive)
void MergeSort(vector<int>& vec, int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        MergeSort(vec, first, mid); //first hald
        MergeSort(vec, mid + 1, last); //second half
        merge(vec, first, mid, last); //merge the sorted halves
    }
}

// MergeIterative Function
void MergeIterative(vector<int>& vecS, vector<int>& vecE, int first, int mid, int last) {
    // Initial Index
    int i = first; //first subarray
    int j = mid + 1; //second subarray
    int k = first; //merged subarray

    // Merge Two Subarrays to vecE
    while (i <= mid && j <= last) {
        if (vecS[i] <= vecS[j]) {
            vecE[k] = vecS[i];
            i++;
        } else {
            vecE[k] = vecS[j];
            j++;
        }
        k++;
    }

    // Copy Remaining Elements (first subarray)
    while (i <= mid) {
        vecE[k] = vecS[i];
        i++;
        k++;
    }

    // Copy Remaining Elements (second subarray)
    while (j <= last) {
        vecE[k] = vecS[j];
        j++;
        k++;
    }
}

// IterativeMergeSort Function
void IterativeMergeSort(vector<int>& vec, int first, int last) {
    int n = last - first + 1; //number of elements to sort
    vector<int> temp(vec.size()); 

    // Pointers to Original/Temporary Vectors
    vector<int>* vecS = &vec;
    vector<int>* vecE = &temp;

    // Merge Subarrays
    for (int i = 1; i <= n; i *= 2) {
        for (int start = first; start <= last; start += 2 * i) {
            int mid = min(start + i - 1, last); //mid index
            int end = min(start + 2 * i - 1, last); //end index
            MergeIterative(*vecS, *vecE, start, mid, end);
        }
        swap(vecS, vecE);
    }

    // Check if Sorted Vector is in Temporary Vector
    if (vecS != &vec) {
        for (int i = first; i <= last; i++) {
            vec[i] = temp[i];
        }
    }
}

// QuickSort Function 
void QuickSort(vector<int>& vec, int first, int last) {
    if (last - first < 4) { //if subarray is small
        MergeSort(vec, first, last);
        return;
    }
    int mid = (first + last) / 2;

    // Sort first, mid, and last Elements
    if (vec[first] > vec[last]) {
        swap(vec[first], vec[last]);
    }
    if (vec[first] > vec[mid]) {
        swap(vec[first], vec[mid]);
    }
    else if (vec[mid] > vec[last]) {
        swap(vec[mid], vec[last]);
    }

    int pivot = vec[mid]; //pivot point
    swap(vec[mid], vec[last - 1]);

    int left = first + 1;
    int right = last - 2;
    bool done = false;

    // Partitioning loop
    while (!done) {
        while (vec[left] < pivot) { //left to right
            left++;
        }
        while (vec[right] > pivot) { //right to left
            right--;
        }
        if (left < right) {
            swap(vec[left], vec[right]);
            left++;
            right--;
        } else {
            done = true; //complete partitioning
        }
    }

    swap(vec[left], vec[last - 1]); //restore pivot to its correct position

    // Recursive Calls for Partitions
    QuickSort(vec, first, left - 1);
    QuickSort(vec, left + 1, last);
}

// ShellSort Function
void ShellSort(vector<int>& vec, int first, int last) {
    int size = last + 1; //vector size
    for (int gap = size / 2; gap > 0; gap /= 2) { //start with a large gap, then reduce by half
        for (int i = gap; i < size; i++) { //iterate over elements starting from the gap
            int temp = vec[i];
            int j;
            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) { //shift elements to the right by gap until temp finds its position
                vec[j] = vec[j - gap];
            }
            vec[j] = temp;
        }
    }
}

#endif