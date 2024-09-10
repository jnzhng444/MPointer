#include <gtest/gtest.h>
#include "Ordenar/BubbleSort.h"
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


// Prueba básica de BubbleSort con una lista desordenada
TEST(BubbleSortTest, BasicSorting) {
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(2);
    list.append(9);
    list.append(1);

    std::cout << "Antes de BubbleSort: ";
    printList(list);

    BubbleSort<int>::sort(list);

    std::cout << "Después de BubbleSort: ";
    printList(list);

    ASSERT_EQ(*list.getHead()->data, 1);
    ASSERT_EQ(*list.getHead()->next->data, 2);
    ASSERT_EQ(*list.getTail()->prev->data, 5);
    ASSERT_EQ(*list.getTail()->data, 9);
}

// Prueba de BubbleSort con una lista ya ordenada
TEST(BubbleSortTest, AlreadySorted) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    std::cout << "Antes de BubbleSort (lista ya ordenada): ";
    printList(list);

    BubbleSort<int>::sort(list);

    std::cout << "Después de BubbleSort: ";
    printList(list);

    ASSERT_EQ(*list.getHead()->data, 1);
    ASSERT_EQ(*list.getHead()->next->data, 2);
    ASSERT_EQ(*list.getTail()->prev->data, 3);
    ASSERT_EQ(*list.getTail()->data, 4);
}

// Prueba de BubbleSort con valores repetidos
TEST(BubbleSortTest, RepeatedValues) {
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(1);
    list.append(5);
    list.append(3);
    list.append(1);

    std::cout << "Antes de BubbleSort (valores repetidos): ";
    printList(list);

    BubbleSort<int>::sort(list);

    std::cout << "Después de BubbleSort: ";
    printList(list);

    auto node = list.getHead();
    ASSERT_EQ(*node->data, 1);
    node = node->next;
    ASSERT_EQ(*node->data, 1);
    node = node->next;
    ASSERT_EQ(*node->data, 3);
    node = node->next;
    ASSERT_EQ(*node->data, 5);
    node = node->next;
    ASSERT_EQ(*node->data, 5);
}
