template <typename T>
MPointerGC* MPointer<T>::gc = MPointerGC::getInstance();

template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.ptr = new T();
    mp.id = gc->registerPointer(static_cast<MPointerBase*>(static_cast<void*>(mp.ptr))); // Usa static_cast a void* y luego a MPointerBase*
    return mp;
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
T* MPointer<T>::operator&() const {
    return ptr;  // Devuelve el puntero al objeto apuntado
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
