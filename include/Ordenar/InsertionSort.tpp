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
        Node<T>* search = sortedHead;

        // Desconectar el nodo actual de la lista original
        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        if (current == list.getHead()) {
            list.setHead(next);
        }

        // Insertar el nodo actual en la lista ordenada
        if (!sortedHead || *current->data < *sortedHead->data) {
            // Insertar al inicio de la lista ordenada
            current->next = sortedHead;
            if (sortedHead) {
                sortedHead->prev = current;
            }
            sortedHead = current;
            sortedHead->prev = nullptr;
        } else {
            // Insertar en la posición adecuada en la lista ordenada
            while (search && search->next && *current->data >= *search->next->data) {
                search = search->next;
            }
            current->next = search->next;
            if (search->next) {
                search->next->prev = current;
            }
            search->next = current;
            current->prev = search;
        }

        current = next;  // Mover al siguiente nodo
    }

    // Actualizar la lista original con la lista ordenada
    list.setHead(sortedHead);
}

#endif // INSERTIONSORT_TPP
