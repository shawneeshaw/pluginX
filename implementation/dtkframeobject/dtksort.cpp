#include "dtksort.h"
#include <assert.h>

#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))

//-----------------------------------------------------------------------------
static void _int_perm_quicksort(int *perm, int *len, int n) {
    int temp;
    if (n <= 1)
        return;

    SWAP(perm[0], perm[(n - 1)/2], temp);

    int i = 0;
    int j = n;
    int t = len[perm[0]];

    while (1) {
        do i++; while (i < n && len[perm[i]] < t);
        do j--; while (len[perm[j]] > t);
        if (j < i) break;
        SWAP(perm[i], perm[j], temp);
    }
    SWAP(perm[0], perm[j], temp);

    _int_perm_quicksort(perm, len, j);
    _int_perm_quicksort(perm + i, len, n - i);
}

//-----------------------------------------------------------------------------
static void _real_perm_quicksort(int *perm, float *len, int n) {
    int temp;
    if (n<= 1) {
        return;
    }
    SWAP(perm[0], perm[(n - 1)/2], temp);
    int i = 0;
    int j = n;
    float t = len[perm[0]];
    while (1) {
        do i++; while (i < n && len[perm[i]] < t);
        do j--; while (len[perm[j]] > t);
        if (j < i) break;
        SWAP(perm[i], perm[j], temp);
    }
    SWAP (perm[0], perm[j], temp);
    _real_perm_quicksort(perm, len, j);
    _real_perm_quicksort(perm + i, len, n - i);
}

//-----------------------------------------------------------------------------
static void _rvereseArray(int arr[], int start, int end) {
    int temp;
    while(start < end) {
        temp = arr[start];   
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }   
}     

//-----------------------------------------------------------------------------
void dtkSort::QuickSort(int array[], int index_array[], int num_entry) {
    //@@preconditions
    assert(num_entry > 0);
    //@@end preconditions

    _int_perm_quicksort(index_array, array, num_entry);
}

//-----------------------------------------------------------------------------
void dtkSort::QuickSort(float array[], int index_array[], int num_entry) {
    //@@preconditions
    assert(num_entry > 0);
    //@@end preconditions

    _real_perm_quicksort(index_array, array, num_entry);
}

//-----------------------------------------------------------------------------
void dtkSort::FilterArray(float array[], int index_array[], int num_entry, int descend) {
    //@@preconditions
    assert(num_entry > 0);
    //@@end preconditions

    float *tmpArray = new float[num_entry];
    for (int i = 0; i < num_entry; i++) {
        tmpArray[i] = array[index_array[i]];
    }
    for (int j = 0; j < num_entry; j++) {
        array[j] = (descend == 1)? tmpArray[j]: tmpArray[num_entry-j-1];
    }
    delete[] tmpArray;
}

//-----------------------------------------------------------------------------
void dtkSort::FilterArray(int array[], int index_array[], int num_entry, int descend) {
    //@@preconditions
    assert(num_entry > 0);
    //@@end preconditions

    int *tmpArray = new int[num_entry];
    for (int i = 0; i < num_entry; i++) {
        tmpArray[i] = array[index_array[i]];
    }
    for (int j = 0; j < num_entry; j++) {
        array[j] = (descend == 1)? tmpArray[j]: tmpArray[num_entry-j-1];
    }
    delete[] tmpArray;
}

//-----------------------------------------------------------------------------
void dtkSort::ReverseArray(int array[], int num_entry) {
    //@@preconditions
    assert(num_entry > 0);
    //@@end preconditions

    _rvereseArray(array, 0, num_entry);
}
