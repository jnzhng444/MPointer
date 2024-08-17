#ifndef BUBBLESORT_TPP
#define BUBBLESORT_TPP

#include "Lista/DoublyLinkedList.h"

template <typename T>
void BubbleSort<T>::sort(DoublyLinkedList<T>& list) {
    if (list.getSize() <= 1) return;

    bool swapped;
    do {
        swapped = false;
        Node<T>* current = list.getHead();
        while (current && current->next) {
            if (*current->data > *current->next->data) {
                // Swap data between current and next
                T temp = *current->data;
                *current->data = *current->next->data;
                *current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

#endif // BUBBLESORT_TPP
