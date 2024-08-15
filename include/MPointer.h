#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* ptr;
    int id;

    MPointer();

public:
    static MPointer<T> New();
    ~MPointer();

    T& operator*();
    T* operator&();

    MPointer<T>& operator=(const MPointer<T>& other);
    MPointer<T>& operator=(const T& value);

    int GetID() const;
};

#include "MPointer.tpp"

#endif // MPOINTER_H
