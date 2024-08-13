#include "MPointer.h"
#include <iostream>

int main() {
    // Iniciar el recolector de basura
    MPointerGC::getInstance()->startGC();

    // Crear un nuevo MPointer para enteros
    MPointer<int> myPtr = MPointer<int>::New();
    // Asignar un valor
    *myPtr = 5;
    // Leer el valor
    int valor = *myPtr;
    std::cout << "Valor de myPtr: " << valor << std::endl; // Debería imprimir 5

    // Crear otro MPointer para enteros
    MPointer<int> myPtr2 = MPointer<int>::New();
    // Asignar un valor
    *myPtr2 = 10;
    std::cout << "Valor de myPtr2: " << *myPtr2 << std::endl; // Debería imprimir 10

    // Asignar myPtr a myPtr2
    myPtr2 = myPtr;
    std::cout << "Valor de myPtr2 después de asignar myPtr: " << *myPtr2 << std::endl; // Debería imprimir 5

    // Asignar un nuevo valor a myPtr
    *myPtr = 6;
    std::cout << "Valor de myPtr después de cambiar el valor: " << *myPtr << std::endl; // Debería imprimir 6
    std::cout << "Valor de myPtr2 después de cambiar el valor de myPtr: " << *myPtr2 << std::endl; // Debería imprimir 6

    // Asignar un valor directamente
    myPtr2 = 7;
    std::cout << "Valor de myPtr2 después de asignar 7: " << *myPtr2 << std::endl; // Debería imprimir 7

    // Detener el recolector de basura antes de finalizar el programa
    MPointerGC::getInstance()->stopGC();

    // Finalizar el programa
    return 0;
}
