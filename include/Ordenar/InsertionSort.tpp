#ifndef INSERTIONSORT_TPP
#define INSERTIONSORT_TPP

#include "Lista/DoublyLinkedList.h"

template <typename T>
void InsertionSort<T>::sort(DoublyLinkedList<T>& list) {
    if (list.getSize() <= 1) return;

    Node<T>* sortedHead = nullptr;  // Lista de nodos ordenados
    Node<T>* current = list.getHead();

    while (current) {
        Node<T>* next = current->next;  // Guardar el siguiente nodo

        // Insertar el nodo actual en la lista ordenada
        if (!sortedHead || *current->data < *sortedHead->data) {
            // Insertar al inicio de la lista ordenada
            current->next = sortedHead;
            if (sortedHead) sortedHead->prev = current;
            sortedHead = current;
            sortedHead->prev = nullptr;
        } else {
            // Insertar en la posición adecuada en la lista ordenada
            Node<T>* search = sortedHead;
            while (search->next && *current->data >= *search->next->data) {
                search = search->next;
            }
            current->next = search->next;
            if (search->next) search->next->prev = current;
            search->next = current;
            current->prev = search;
        }

        current = next;  // Mover al siguiente nodo
    }

    // Limpiar la lista original
    list.clear();

    // Actualizar la lista original con la lista ordenada
    Node<T>* node = sortedHead;
    while (node) {
        list.append(*node->data);
        node = node->next;
    }
}

#endif // INSERTIONSORT_TPP
