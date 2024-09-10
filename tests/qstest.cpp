#include <gtest/gtest.h>
#include "Ordenar/QuickSort.h"
#include <iostream>

// Función auxiliar para imprimir el estado de la lista
inline void printList(const DoublyLinkedList<int>& list) {
    auto node = list.getHead();
    std::cout << "Lista: ";
    while (node) {
        std::cout << *node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}


// Prueba básica de QuickSort con una lista desordenada
TEST(QuickSortTest, BasicSorting) {
    DoublyLinkedList<int> list;
    list.append(3);
    list.append(1);
    list.append(2);

    std::cout << "Antes de QuickSort: ";
    printList(list);

    QuickSort<int>::sort(list);

    std::cout << "Después de QuickSort: ";
    printList(list);

    ASSERT_EQ(*list.getHead()->data, 1);
    ASSERT_EQ(*list.getHead()->next->data, 2);
    ASSERT_EQ(*list.getTail()->data, 3);
}

// Prueba de QuickSort con una lista ya ordenada
TEST(QuickSortTest, AlreadySorted) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    std::cout << "Antes de QuickSort (lista ya ordenada): ";
    printList(list);

    QuickSort<int>::sort(list);

    std::cout << "Después de QuickSort: ";
    printList(list);

    ASSERT_EQ(*list.getHead()->data, 1);
    ASSERT_EQ(*list.getHead()->next->data, 2);
    ASSERT_EQ(*list.getTail()->data, 3);
}

// Prueba de QuickSort con valores repetidos
TEST(QuickSortTest, RepeatedValues) {
    DoublyLinkedList<int> list;
    list.append(3);
    list.append(1);
    list.append(3);
    list.append(2);
    list.append(1);

    std::cout << "Antes de QuickSort (valores repetidos): ";
    printList(list);

    QuickSort<int>::sort(list);

    std::cout << "Después de QuickSort: ";
    printList(list);

    auto node = list.getHead();
    ASSERT_EQ(*node->data, 1);
    node = node->next;
    ASSERT_EQ(*node->data, 1);
    node = node->next;
    ASSERT_EQ(*node->data, 2);
    node = node->next;
    ASSERT_EQ(*node->data, 3);
    node = node->next;
    ASSERT_EQ(*node->data, 3);
}
