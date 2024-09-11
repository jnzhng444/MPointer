#include <gtest/gtest.h>
#include "Ordenar/InsertionSort.h"
#include <iostream>

// Función auxiliar para imprimir el estado de la lista (igual que antes)
inline void printList(const DoublyLinkedList<int>& list) {
    auto node = list.getHead();
    std::cout << "Lista: ";
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

TEST(InsertionSortTest, EmptyList) {
    DoublyLinkedList<int> list;

    std::cout << "Antes de InsertionSort (lista vacía): ";
    printList(list);

    InsertionSort<int>::sort(list);

    std::cout << "Después de InsertionSort: ";
    printList(list);

    ASSERT_EQ(list.getSize(), 0);
    ASSERT_EQ(list.getHead(), nullptr);
}

TEST(InsertionSortTest, SingleElement) {
    DoublyLinkedList<int> list;
    list.append(5);

    std::cout << "Antes de InsertionSort (un solo elemento): ";
    printList(list);

    InsertionSort<int>::sort(list);

    std::cout << "Después de InsertionSort: ";
    printList(list);

    ASSERT_EQ(list.getSize(), 1);
    ASSERT_EQ(*list.getHead()->data, 5);
}



