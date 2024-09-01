// test_insertion_sort.cpp
#include "DoublyLinkedList.h"
#include "InsertionSortPtr.cpp" // Asegúrate de que las implementaciones estén incluidas aquí
#include <gtest/gtest.h>

TEST(InsertionSortTest, BasicSorting) {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);

    insertionSort(list);

    std::vector<int> expected = {1, 2, 4, 6, 9};
    MPointer<Node<int>> current = list.head;
    for (int val : expected) {
        ASSERT_EQ(*(current->data), val);
        current = current->next;
    }
}

TEST(InsertionSortTest, EmptyList) {
    DoublyLinkedList<int> list;

    insertionSort(list);

    ASSERT_EQ(list.head, nullptr);
    ASSERT_EQ(list.tail, nullptr);
}

TEST(InsertionSortTest, SingleElementList) {
    DoublyLinkedList<int> list;
    list.append(5);

    insertionSort(list);

    ASSERT_NE(list.head, nullptr);
    ASSERT_NE(list.tail, nullptr);
    ASSERT_EQ(*(list.head->data), 5);
    ASSERT_EQ(*(list.tail->data), 5);
}

TEST(InsertionSortTest, AlreadySortedList) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    insertionSort(list);

    std::vector<int> expected = {1, 2, 3, 4, 5};
    MPointer<Node<int>> current = list.head;
    for (int val : expected) {
        ASSERT_EQ(*(current->data), val);
        current = current->next;
    }
}

TEST(InsertionSortTest, ReversedList) {
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(1);

    insertionSort(list);

    std::vector<int> expected = {1, 2, 3, 4, 5};
    MPointer<Node<int>> current = list.head;
    for (int val : expected) {
        ASSERT_EQ(*(current->data), val);
        current = current->next;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Compilar con: g++ -std=c++14 -isystem /usr/include/gtest -pthread test_insertionsort.cpp -lgtest -lgtest_main -o test_insertionsort
Ejecutar con: ./test_insertionsort
*/