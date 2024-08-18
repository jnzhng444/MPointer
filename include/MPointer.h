#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* ptr;  // Puntero al tipo T
    int id;  // ID en el garbage collector

    MPointer();  // Constructor privado

public:
    static MPointer<T> New();  // Método estático para crear un nuevo MPointer
    ~MPointer();  // Destructor

    T& operator*();  // Sobrecarga del operador *
    T* operator&();  // Sobrecarga del operador & para devolver la dirección

    MPointer<T>& operator=(const MPointer<T>& other);  // Sobrecarga del operador =
    MPointer<T>& operator=(const T& value);  // Sobrecarga del operador = para asignación de valor directo

    int GetID() const;  // Obtiene el ID del MPointer
};

#include "MPointer.tpp"

#endif // MPOINTER_H
