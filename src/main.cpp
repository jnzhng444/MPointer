#include <iostream>
#include "MPointer.h"
#include "MPointerGC.h"
#include "Lista/DoublyLinkedList.h"
#include "Ordenar/BubbleSort.h"
#include "Ordenar/InsertionSort.h"
#include "Ordenar/QuickSort.h"

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
    list.append(3);
    list.append(223);
    list.append(4);
    list.append(77);
    list.append(5);
    list.append(924);
    list.append(23);
    list.append(41);
    list.append(7711);
    list.append(5);
    list.append(1);

    std::cout << " Lista antes de ordenar:" << std::endl;
    Node<int>* node = list.getHead();
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;

    // Selecciona y aplica el algoritmo de ordenamiento
    QuickSort<int>::sort(list);
    //BubbleSort<int>::sort(list);
    //InsertionSort<int>::sort(list);


    std::cout << "Lista despues de ordenar:" << std::endl;
    node = list.getHead();
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;



    return 0;
}
