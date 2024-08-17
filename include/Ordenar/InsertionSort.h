#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "Lista/DoublyLinkedList.h"

template <typename T>
class InsertionSort {
public:
    static void sort(DoublyLinkedList<T>& list);
};

#include "InsertionSort.tpp"

#endif // INSERTIONSORT_H
