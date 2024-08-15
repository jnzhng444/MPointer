#include <iostream>
#include "MPointer.h"
#include "MPointerGC.h"

int main() {
    MPointerGC::GetInstance().StartGarbageCollector();

    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 5;

    MPointer<int> myPtr2 = MPointer<int>::New();
    myPtr2 = myPtr;

    std::cout << "Valor de myPtr: " << *myPtr << std::endl;
    std::cout << "Valor de myPtr2: " << *myPtr2 << std::endl;

    return 0;
}
