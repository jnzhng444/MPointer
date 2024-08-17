#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Lista/DoublyLinkedList.h"

template <typename T>
class QuickSort {
public:
    static void sort(DoublyLinkedList<T>& list);

private:
    static Node<T>* partition(DoublyLinkedList<T>& list, Node<T>* low, Node<T>* high);
    static void quickSortRec(DoublyLinkedList<T>& list, Node<T>* low, Node<T>* high);
};

#include "QuickSort.tpp"

#endif // QUICKSORT_H
