#ifndef MPOINTER_TPP
#define MPOINTER_TPP

#include "MPointer.h"

template <typename T>
MPointer<T>::MPointer() {
    ptr = new T();
    id = MPointerGC::GetInstance().RegisterPointer(ptr);
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    return MPointer<T>();
}

template <typename T>
MPointer<T>::~MPointer() {
    MPointerGC::GetInstance().DeregisterPointer(id);
    delete ptr;
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        MPointerGC::GetInstance().DeregisterPointer(id);
        ptr = other.ptr;
        id = other.id;
        MPointerGC::GetInstance().IncrementRefCount(id);
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    *ptr = value;
    return *this;
}

template <typename T>
int MPointer<T>::GetID() const {
    return id;
}

#endif // MPOINTER_TPP
