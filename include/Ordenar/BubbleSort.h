#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "Lista/DoublyLinkedList.h"

template <typename T>
class BubbleSort {
public:
    static void sort(DoublyLinkedList<T>& list);
};

#include "BubbleSort.tpp"

#endif // BUBBLESORT_H
