
#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>

#include "pubdef.h"

void SelectionSort(elemtype arr[], int len);

void InsertionSort(elemtype arr[], int len);

void ShellSort(elemtype arr[], int len);

void HeapSort(elemtype arr[], int len);

void MergeSort(elemtype arr[], int len);

void QuickSort(elemtype arr[], int len);

#endif /* __SORT_H__ */
