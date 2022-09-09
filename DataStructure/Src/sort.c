
#include "sort.h"


#define array_swap(arr, i, j) do {  \
    int temp = arr[i];              \
    arr[i] = arr[j];                \
    arr[j] = temp;                  \
} while (0)


void SelectionSort(elemtype arr[], int len) {
    int min;
    for (int i = 0; i < len - 1; i++) {
        min = i;
        for (int j = i + 1; j < len; j++)
            if (arr[j] < arr[min])
                min = j;
        array_swap(arr, min, i);
    }
}


void InsertionSort(elemtype arr[], int len) {
    for (int i = 0; i < len; i++) {
        elemtype temp = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > temp; j--)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}


void ShellSort(elemtype arr[], int len) {
    for (int inc = len / 2; inc > 0; inc /= 2)
        for (int i = inc; i < len; i++) {
            elemtype temp = arr[i];
            int j;
            for (j = i; j >= inc; j -= inc)
                if (temp < arr[j - inc])
                    arr[j] = arr[j - inc];
                else
                    break;
            arr[j] = temp;
        }
}

#define leftchild(pos) (2 * (pos) + 1)

static void PercolateDown(elemtype arr[], int len, int pos) {
    int child;
    elemtype temp;
    for (temp = arr[pos]; leftchild(pos) < len; pos = child) {
        child = leftchild(pos);
        if (child != len - 1 && arr[child + 1] > arr[child])
            child++;
        if (temp < arr[child])
            arr[pos] = arr[child];
        else
            break;
    }
    arr[pos] = temp;
}

void HeapSort(elemtype arr[], int len) {
    for (int i = len / 2; i >= 0; i--)
        PercolateDown(arr, len, i); // build heap
    for (int i = len - 1; i > 0; i--) {
        array_swap(arr, 0, i);      // delete max
        PercolateDown(arr, i, 0);
    }
}


static void Merge(elemtype arr[], elemtype temp[], 
                  int left, int right, int end) {
    int leftend = right - 1;
    int elems = end - left + 1;
    int curpos = left;

    while(left <= leftend && right <= end)
        if (arr[left] <= arr[ right ])
            temp[curpos++] = arr[left++];
        else
            temp[curpos++] = arr[right++];

    while (left <= leftend) // Copy rest of first half
        temp[curpos++] = arr[left++];
    while (right <= end)    // Copy rest of second half
        temp[curpos++] = arr[right++];

    for (int i = 0; i < elems; i++, end--)
        arr[end] = temp[end];  // Copy temp back
}



void _MergeSort(elemtype arr[], elemtype temp[], int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        _MergeSort(arr, temp, left, center);
        _MergeSort(arr, temp, center + 1, right);
        Merge(arr, temp, left, center + 1, right);
    }
}


void MergeSort(elemtype arr[], int len) {
    elemtype* temp = malloc(sizeof(elemtype) * len);
    if (temp) {
        _MergeSort(arr, temp, 0, len - 1);
        free(temp);
    }
}




static elemtype Median3(elemtype arr[], int left, int right) {
    int center = (left + right) / 2;
    if (arr[left] > arr[center])
        array_swap(arr, left, center);
    if (arr[left] > arr[right])
        array_swap(arr, left, right);
    if (arr[center] > arr[right])
        array_swap(arr, center, right);
    array_swap(arr, center, right - 1);  // hide pivot
    return arr[right - 1];               // return pivot
}

#define QUICKSORT_CUTOFF (3)

static void _QuickSort(elemtype arr[], int left, int right) {
    if (left + QUICKSORT_CUTOFF <= right) {
        elemtype pivot = Median3(arr, left, right);
        int i = left; 
        int j = right - 1;
        while (1) {
            while (arr[++i] < pivot) continue;
            while (arr[--j] > pivot) continue;
            if (i < j)
                array_swap(arr, i, j);
            else
                break;
        }
        array_swap(arr, i, right - 1);  // restore pivot
        _QuickSort(arr, left, i - 1);
        _QuickSort(arr, i + 1, right);
    }
    else  // do an insertion sort on the subarray
        InsertionSort( arr + left, right - left + 1 );
}

void QuickSort(elemtype arr[], int len) {
    _QuickSort(arr, 0, len - 1);
}





int BinarySearch(const int arr[], int len, int elem) {
    int left = 0; 
    int right = len - 1;
    while (left <= right) {
        int mid = (right + left) / 2;
        if (arr[mid] == elem)
            return mid; 
        else if (arr[mid] < elem)
            left = mid + 1;
        else if (arr[mid] > elem)
            right = mid - 1;
        }
    return -1;
}

