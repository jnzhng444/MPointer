#ifndef NODE_H
#define NODE_H

#include "MPointer.h"

template <typename T>
class Node {
public:
    MPointer<T> data;  // Datos del nodo encapsulados en MPointer
    Node<T>* prev;     // Puntero al nodo anterior
    Node<T>* next;     // Puntero al nodo siguiente

    Node(const T& value) : data(MPointer<T>::New()), prev(nullptr), next(nullptr) {
        *data = value;  // Asignar el valor al puntero interno
    }
};

#endif // NODE_H
