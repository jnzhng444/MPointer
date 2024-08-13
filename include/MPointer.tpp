#include "MPointer.h"

template <typename T>
MPointerGC* MPointer<T>::gc = MPointerGC::getInstance();

template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.ptr = new T();
    // Registrar el puntero al objeto MPointer<T> en lugar del puntero al objeto T
    mp.id = gc->registerPointer(&mp);
    return mp;
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
T* MPointer<T>::operator->() const {
    return ptr;  // Devuelve el puntero al objeto apuntado
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        // Desregistrar el puntero actual
        gc->unregisterPointer(id);

        // Copiar el puntero y el id del objeto "other"
        ptr = other.ptr;
        id = other.id;

        // Incrementar el recuento de referencias del puntero copiado
        gc->increaseRefCount(id);
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    *ptr = value;
    return *this;
}

template <typename T>
MPointer<T>::~MPointer() {
    gc->unregisterPointer(id);
    delete ptr;
}
