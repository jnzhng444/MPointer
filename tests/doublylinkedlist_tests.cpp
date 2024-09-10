#include <gtest/gtest.h>
#include "Lista/DoublyLinkedList.h"

// Prueba de agregar elementos al final de la lista
TEST(DoublyLinkedListTest, AppendElements) {
    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    ASSERT_EQ(list.getSize(), 3);  // Verificamos que el tamaño de la lista es correcto

    auto node = list.getHead();
    ASSERT_EQ(*node->data, 10);  // Verificamos que los valores son correctos
    node = node->next;
    ASSERT_EQ(*node->data, 20);
    node = node->next;
    ASSERT_EQ(*node->data, 30);
}

// Prueba de agregar elementos al inicio de la lista
TEST(DoublyLinkedListTest, PrependElements) {
    DoublyLinkedList<int> list;
    list.prepend(30);
    list.prepend(20);
    list.prepend(10);

    ASSERT_EQ(list.getSize(), 3);  // Verificamos que el tamaño de la lista es correcto

    auto node = list.getHead();
    ASSERT_EQ(*node->data, 10);  // Verificamos que los valores son correctos
    node = node->next;
    ASSERT_EQ(*node->data, 20);
    node = node->next;
    ASSERT_EQ(*node->data, 30);
}

// Prueba de eliminación de nodos
TEST(DoublyLinkedListTest, RemoveElement) {
    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    auto node = list.getHead()->next;  // Nodo con valor 20
    list.remove(node);

    ASSERT_EQ(list.getSize(), 2);  // Verificamos que el tamaño es correcto después de la eliminación

    node = list.getHead();
    ASSERT_EQ(*node->data, 10);  // Verificamos que los valores son correctos después de la eliminación
    node = node->next;
    ASSERT_EQ(*node->data, 30);
}

// Prueba de limpiar la lista
TEST(DoublyLinkedListTest, ClearList) {
    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    list.clear();

    ASSERT_EQ(list.getSize(), 0);  // Verificar que el tamaño es 0
    ASSERT_EQ(list.getHead(), nullptr);  // Verificar que la cabeza es nullptr
}
