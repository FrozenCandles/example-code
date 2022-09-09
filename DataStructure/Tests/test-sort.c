//
// Created by Hello on 2022-08-21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#define N 24
#define reset() memcpy(randoms, randoms_original, N * sizeof(int))
#define array_print(arr) for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) printf("%d ", arr[i])

void test_sort(void) {

    srand(10);

    int randoms[N], randoms_original[N];

    for (int i = 0; i < N; i++)
        randoms_original[i] = rand() % 100;

    reset();
    printf("Original array :");
    array_print(randoms);
    putchar('\n');

    printf("Selection sort :");
    SelectionSort(randoms, N);
    array_print(randoms);
    putchar('\n');

    printf("Insertion sort :");
    InsertionSort(randoms, N);
    array_print(randoms);
    putchar('\n');

    reset();
    printf("Shell sort     :");
    ShellSort(randoms, N);
    array_print(randoms);
    putchar('\n');

    reset();
    printf("Heap sort      :");
    HeapSort(randoms, N);
    array_print(randoms);
    putchar('\n');

    reset();
    printf("Merge sort     :");
    MergeSort(randoms, N);
    array_print(randoms);
    putchar('\n');

    reset();
    printf("Quick sort     :");
    QuickSort(randoms, N);
    array_print(randoms);
    putchar('\n');




}

