#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer : public MPointerBase {
private:
    T* ptr; // Puntero encapsulado
    int id; // ID único asignado por MPointerGC
    static MPointerGC* gc; // Referencia a MPointerGC

public:
    static MPointer<T> New(); // Método para crear un nuevo MPointer

    T& operator*();   // Sobrecarga del operador *
    T* operator->() const;  // Sobrecarga del operador -> para acceder a los miembros del objeto apuntado

    MPointer<T>& operator=(const MPointer<T>& other); // Asignación entre MPointers
    MPointer<T>& operator=(const T& value); // Asignación de valor directo

    ~MPointer(); // Destructor
};

#include "MPointer.tpp" // Incluye la implementación del template

#endif
