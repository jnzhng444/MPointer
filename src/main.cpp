#include <iostream>
#include "MPointer.h"
#include "MPointerGC.h"
#include "Lista/DoublyLinkedList.h"

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

    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.prepend(5);
    list.append(15);

    std::cout << "Lista antes de ordenar:" << std::endl;
    Node<int>* node = list.getHead();
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;

    return 0;
}
