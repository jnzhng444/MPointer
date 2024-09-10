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

// Prueba básica de InsertionSort con una lista desordenada
TEST(InsertionSortTest, BasicSorting) {
    DoublyLinkedList<int> list;
    list.append(8);
    list.append(3);
    list.append(7);
    list.append(2);

    std::cout << "Antes de InsertionSort: ";
    printList(list);

    InsertionSort<int>::sort(list);

    std::cout << "Después de InsertionSort: ";
    printList(list);

    ASSERT_EQ(*list.getHead()->data, 2);
    ASSERT_EQ(*list.getHead()->next->data, 3);
    ASSERT_EQ(*list.getHead()->next->next->data, 7);
    ASSERT_EQ(*list.getTail()->data, 8);
}

// Prueba de InsertionSort con una lista ya ordenada
TEST(InsertionSortTest, AlreadySorted) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    std::cout << "Antes de InsertionSort (lista ya ordenada): ";
    printList(list);

    InsertionSort<int>::sort(list);

    std::cout << "Después de InsertionSort: ";
    printList(list);

    ASSERT_EQ(*list.getHead()->data, 1);
    ASSERT_EQ(*list.getHead()->next->data, 2);
    ASSERT_EQ(*list.getTail()->prev->data, 3);
    ASSERT_EQ(*list.getTail()->data, 4);
}

// Prueba de InsertionSort con valores repetidos
TEST(InsertionSortTest, RepeatedValues) {
    DoublyLinkedList<int> list;
    list.append(3);
    list.append(2);
    list.append(3);
    list.append(1);
    list.append(2);

    std::cout << "Antes de InsertionSort (valores repetidos): ";
    printList(list);

    InsertionSort<int>::sort(list);

    std::cout << "Después de InsertionSort: ";
    printList(list);

    auto node = list.getHead();
    ASSERT_EQ(*node->data, 1);
    node = node->next;
    ASSERT_EQ(*node->data, 2);
    node = node->next;
    ASSERT_EQ(*node->data, 2);
    node = node->next;
    ASSERT_EQ(*node->data, 3);
    node = node->next;
    ASSERT_EQ(*node->data, 3);
}
