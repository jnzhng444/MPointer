#include <iostream>
#include "MPointer.h"
#include "Lista/DoublyLinkedList.h"
#include "Ordenar/BubbleSort.h"
#include "Ordenar/InsertionSort.h"
#include "Ordenar/QuickSort.h"

int main() {
    // Crear un primer MPointer y asignarle un valor
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;
    std::cout << "ptr1 ID: " << ptr1.GetID() << ", Value: " << *ptr1 << std::endl;
    MPointerGC::GetInstance().debug();

    // Crear un segundo MPointer copiando ptr1
    auto ptrpop = ptr1;
    std::cout << "ptrpop ID: " << ptrpop.GetID() << ", Value: " << *ptrpop << std::endl;
    MPointerGC::GetInstance().debug();

    // Crear un segundo MPointer copiando ptr1
    auto ptr2 = ptr1;
    std::cout << "ptr2 ID: " << ptr2.GetID() << ", Value: " << *ptr2 << std::endl;
    MPointerGC::GetInstance().debug();

    // Modificar el valor a través de ptr2 y mostrar cómo cambia ptr1
    *ptr2 = 100;
    std::cout << "After modifying ptr2, ptr1 Value: " << *ptr1 << std::endl;
    MPointerGC::GetInstance().debug();

    // Crear un tercer MPointer y asignarle un valor diferente
    auto ptr3 = MPointer<int>::New();
    *ptr3 = 256;
    std::cout << "ptr3 ID: " << ptr3.GetID() << ", Value: " << *ptr3 << std::endl;
    MPointerGC::GetInstance().debug();

    // Finalizar la ejecución
    std::cout << "Program finished, waiting for garbage collector..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Esperar para observar el garbage collector
    MPointerGC::GetInstance().debug();

    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.prepend(5);
    list.append(15);
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

    std::cout << "Lista antes de ordenar:" << std::endl;
    Node<int>* node = list.getHead();
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
    MPointerGC::GetInstance().debug();

    // Selecciona y aplica el algoritmo de ordenamiento
    //QuickSort<int>::sort(list);
    //BubbleSort<int>::sort(list);
    InsertionSort<int>::sort(list);


    std::cout << "Lista despues de ordenar:" << std::endl;
    node = list.getHead();
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
    MPointerGC::GetInstance().debug();

    return 0;
}
