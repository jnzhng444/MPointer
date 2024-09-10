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
    if (id == -1) {
        std::cout << "Pointer already invalidated, skipping destruction." << std::endl;
        return;
    }

    int currentRefCount = MPointerGC::GetInstance().GetRefCount(id);
    std::cout << "Destroying MPointer with ID: " << id << ", current ref_count: " << currentRefCount << std::endl;

    MPointerGC::GetInstance().DeregisterPointer(id);

    currentRefCount = MPointerGC::GetInstance().GetRefCount(id);
    if (currentRefCount == -1) {
        std::cout << "MPointer with ID: " << id << " successfully deregistered and deleted." << std::endl;
    } else {
        std::cout << "MPointer with ID: " << id << " still exists with ref_count: " << currentRefCount << std::endl;
    }
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
MPointer<T>& MPointer<T>::operator=(std::nullptr_t) {
    if (ptr) {
        MPointerGC::GetInstance().DeregisterPointer(id);  // Eliminar el puntero del garbage collector
        ptr = nullptr;
        id = -1;  // Establecer el ID como inválido
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        // Deregistrar el puntero actual
        MPointerGC::GetInstance().DeregisterPointer(id);

        // Asignar el nuevo puntero
        ptr = other.ptr;
        id = other.id;

        // Incrementar el contador de referencias del nuevo puntero
        MPointerGC::GetInstance().IncrementRefCount(id);
    }
    return *this;
}

template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    ptr = other.ptr;
    id = other.id;
    MPointerGC::GetInstance().IncrementRefCount(id);  // Incrementar el contador de referencias
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
