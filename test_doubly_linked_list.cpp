// test_doubly_linked_list.cpp
#include "DoublyLinkedList.h"
#include <gtest/gtest.h>

// Test para la función append
TEST(DoublyLinkedListTest, AppendElements) {
    DoublyLinkedList<int> list;

    list.append(1);
    list.append(2);
    list.append(3);

    ASSERT_NE(list.head, nullptr);
    ASSERT_EQ(*(list.head->data), 1);

    ASSERT_NE(list.head->next, nullptr);
    ASSERT_EQ(*(list.head->next->data), 2);

    ASSERT_NE(list.tail, nullptr);
    ASSERT_EQ(*(list.tail->data), 3);

    ASSERT_EQ(list.tail->next, nullptr);
}

// Test para lista vacía
TEST(DoublyLinkedListTest, EmptyList) {
    DoublyLinkedList<int> list;

    ASSERT_EQ(list.head, nullptr);
    ASSERT_EQ(list.tail, nullptr);
}

// Test para la impresión de la lista
TEST(DoublyLinkedListTest, PrintList) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    testing::internal::CaptureStdout();
    list.printList();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "1 2 3 \n");
}

// Test para un solo elemento en la lista
TEST(DoublyLinkedListTest, SingleElement) {
    DoublyLinkedList<int> list;
    list.append(42);

    ASSERT_NE(list.head, nullptr);
    ASSERT_EQ(*(list.head->data), 42);

    ASSERT_EQ(list.head, list.tail);
    ASSERT_EQ(list.head->next, nullptr);
    ASSERT_EQ(list.head->prev, nullptr);
}

// Test para verificar el enlace doble (prev y next)
TEST(DoublyLinkedListTest, DoublyLinkedNodes) {
    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    ASSERT_EQ(list.head->prev, nullptr);
    ASSERT_EQ(list.head->next->prev, list.head);
    ASSERT_EQ(list.tail->prev->next, list.tail);
    ASSERT_EQ(list.tail->next, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* 
Compilar con: g++ -std=c++14 -isystem /usr/include/gtest -pthread test_doubly_linked_list.cpp -lgtest -lgtest_main -o test_doubly_linked_list
Ejecutar con: ./test_doubly_linked_list
*/