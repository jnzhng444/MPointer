#ifndef QUICKSORT_TPP
#define QUICKSORT_TPP

#include "Lista/DoublyLinkedList.h"

template <typename T>
Node<T>* QuickSort<T>::partition(DoublyLinkedList<T>& list, Node<T>* low, Node<T>* high) {
    T pivot = *high->data;
    Node<T>* i = low->prev;

    for (Node<T>* j = low; j != high; j = j->next) {
        if (*j->data < pivot) {
            i = (i == nullptr) ? low : i->next;
            // Swap data between i and j
            T temp = *i->data;
            *i->data = *j->data;
            *j->data = temp;
        }
    }
    i = (i == nullptr) ? low : i->next;
    // Swap data between i and high
    T temp = *i->data;
    *i->data = *high->data;
    *high->data = temp;

    return i;
}

template <typename T>
void QuickSort<T>::quickSortRec(DoublyLinkedList<T>& list, Node<T>* low, Node<T>* high) {
    if (high != nullptr && low != high && low != high->next) {
        Node<T>* p = partition(list, low, high);
        quickSortRec(list, low, p->prev);
        quickSortRec(list, p->next, high);
    }
}

template <typename T>
void QuickSort<T>::sort(DoublyLinkedList<T>& list) {
    Node<T>* high = list.getTail();
    quickSortRec(list, list.getHead(), high);
}

#endif // QUICKSORT_TPP
