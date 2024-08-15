#include <iostream>
#include "MPointer.h"
#include "MPointerGC.h"

int main() {
    MPointerGC::GetInstance().StartGarbageCollector();

    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 5;

    MPointer<int> myPtr2 = MPointer<int>::New();
    myPtr2 = myPtr;  // Ahora ambos apuntan al mismo int

    std::cout << "Valor de myPtr: " << *myPtr << std::endl;
    std::cout << "Valor de myPtr2: " << *myPtr2 << std::endl;

    myPtr2 = 10;  // Asignación directa, equivalente a *myPtr2 = 10
    std::cout << "Nuevo valor de myPtr2: " << *myPtr2 << std::endl;

    int valor = &myPtr;  // Utilizando el operador & para obtener el valor
    std::cout << "Valor obtenido con &: " << valor << std::endl;

    return 0;
}
