#ifndef MPOINTER_TPP
#define MPOINTER_TPP

#include "MPointer.h"

template <typename T>
MPointer<T>::MPointer() {
    ptr = new T();  // Reservar memoria para un objeto de tipo T
    id = MPointerGC::GetInstance().RegisterPointer(ptr, [](void* p) {
        delete static_cast<T*>(p);  // Función de eliminación para este tipo
    });
    std::cout << "MPointer created with ID: " << id << std::endl;
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    return MPointer<T>();  // Crear una nueva instancia de MPointer
}

template <typename T>
MPointer<T>::~MPointer() {
    int currentRefCount = MPointerGC::GetInstance().GetRefCount(id);  // Obtener el contador de referencias actual
    std::cout << "Destroying MPointer with ID: " << id << ", current ref_count: " << currentRefCount << std::endl;
    MPointerGC::GetInstance().DeregisterPointer(id);  // Eliminar el puntero del garbage collector
}


template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;  // Retornar la referencia al objeto al que apunta
}

template <typename T>
T* MPointer<T>::operator&() {
    return ptr;  // Retornar el valor almacenado en el puntero
}

template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    ptr = other.ptr;
    id = other.id;
    MPointerGC::GetInstance().IncrementRefCount(id);  // Incrementar contador de referencias
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        MPointerGC::GetInstance().DeregisterPointer(id);  // Eliminar el puntero actual del garbage collector
        ptr = other.ptr;  // Copiar el puntero
        id = other.id;  // Copiar el ID
        MPointerGC::GetInstance().IncrementRefCount(id);  // Incrementar el contador de referencias
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    *ptr = value;  // Asignar el valor al puntero interno
    return *this;
}

template <typename T>
int MPointer<T>::GetID() const {
    return id;  // Retornar el ID del MPointer
}

#endif // MPOINTER_TPP
