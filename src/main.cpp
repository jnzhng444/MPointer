#include "MPointer.h"
#include <iostream>

int main() {
    // Crear un nuevo MPointer para enteros
    MPointer<int> ptr1 = MPointer<int>::New();

    // Asignar un valor
    *ptr1 = 42;

    // Imprimir el valor
    std::cout << "Valor de ptr1: " << *ptr1 << std::endl;

    // Crear otro MPointer para enteros
    MPointer<int> ptr2 = MPointer<int>::New();

    // Asignar un valor
    *ptr2 = 99;

    // Imprimir el valor
    std::cout << "Valor de ptr2: " << *ptr2 << std::endl;

    // Terminar el programa, debería desencadenar la recolección de basura
    return 0;
}
