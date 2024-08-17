#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Node.h"

// Declaración de la clase plantilla DoublyLinkedList
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;   // Cabeza de la lista
    Node<T>* tail;   // Cola de la lista
    size_t size;     // Tamaño de la lista

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void append(const T& value);
    void prepend(const T& value);
    void remove(Node<T>* node);
    void clear();

    size_t getSize() const;
    Node<T>* getHead() const;
    Node<T>* getTail() const;

    // Prevención de copias
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
};

// Incluir la implementación de la plantilla
#include "DoublyLinkedList.tpp"

#endif // DOUBLYLINKEDLIST_H
