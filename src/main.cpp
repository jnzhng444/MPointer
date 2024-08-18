#include <iostream>
#include "MPointer.h"

int main() {
    // Crear un primer MPointer y asignarle un valor
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;
    std::cout << "ptr1 ID: " << ptr1.GetID() << ", Value: " << *ptr1 << std::endl;

    // Crear un segundo MPointer copiando ptr1
    auto ptr2 = ptr1;
    std::cout << "ptr2 ID: " << ptr2.GetID() << ", Value: " << *ptr2 << std::endl;

    // Modificar el valor a través de ptr2 y mostrar cómo cambia ptr1
    *ptr2 = 100;
    std::cout << "After modifying ptr2, ptr1 Value: " << *ptr1 << std::endl;

    // Crear un tercer MPointer y asignarle un valor diferente
    auto ptr3 = MPointer<int>::New();
    *ptr3 = 256;
    std::cout << "ptr3 ID: " << ptr3.GetID() << ", Value: " << *ptr3 << std::endl;

    // Finalizar la ejecución
    std::cout << "Program finished, waiting for garbage collector..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Esperar para observar el garbage collector
    return 0;
}
