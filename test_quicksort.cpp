// test_quicksort.cpp
#include "DoublyLinkedList.h"
#include "QuickSortPtr.cpp" // Asegúrate de que las implementaciones estén incluidas aquí
#include <gtest/gtest.h>

TEST(QuickSortTest, BasicSorting) {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);

    quicksort(list.head, list.tail);

    std::vector<int> expected = {1, 2, 4, 6, 9};
    MPointer<Node<int>> current = list.head;
    for (int val : expected) {
        ASSERT_EQ(*(current->data), val);
        current = current->next;
    }
}

TEST(QuickSortTest, EmptyList) {
    DoublyLinkedList<int> list;

    quicksort(list.head, list.tail);

    ASSERT_EQ(list.head, nullptr);
    ASSERT_EQ(list.tail, nullptr);
}

TEST(QuickSortTest, SingleElementList) {
    DoublyLinkedList<int> list;
    list.append(5);

    quicksort(list.head, list.tail);

    ASSERT_NE(list.head, nullptr);
    ASSERT_NE(list.tail, nullptr);
    ASSERT_EQ(*(list.head->data), 5);
    ASSERT_EQ(*(list.tail->data), 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* 
Compilar con: g++ -std=c++14 -isystem /usr/include/gtest -pthread test_quicksort.cpp -lgtest -lgtest_main -o test_quicksort
Ejecutar con: ./test_quicksort
*/