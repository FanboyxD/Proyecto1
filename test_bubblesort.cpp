// test_bubble_sort.cpp
#include "DoublyLinkedList.h"
#include "BubbleSortPtr.cpp" // Asegúrate de que las implementaciones estén incluidas aquí
#include <gtest/gtest.h>

TEST(BubbleSortTest, BasicSorting) {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);

    bubbleSort(list);

    std::vector<int> expected = {1, 2, 4, 6, 9};
    MPointer<Node<int>> current = list.head;
    for (int val : expected) {
        ASSERT_EQ(*(current->data), val);
        current = current->next;
    }
}

TEST(BubbleSortTest, EmptyList) {
    DoublyLinkedList<int> list;

    bubbleSort(list);

    ASSERT_EQ(list.head, nullptr);
    ASSERT_EQ(list.tail, nullptr);
}

TEST(BubbleSortTest, SingleElementList) {
    DoublyLinkedList<int> list;
    list.append(5);

    bubbleSort(list);

    ASSERT_NE(list.head, nullptr);
    ASSERT_NE(list.tail, nullptr);
    ASSERT_EQ(*(list.head->data), 5);
    ASSERT_EQ(*(list.tail->data), 5);
}

TEST(BubbleSortTest, AlreadySortedList) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    bubbleSort(list);

    std::vector<int> expected = {1, 2, 3, 4, 5};
    MPointer<Node<int>> current = list.head;
    for (int val : expected) {
        ASSERT_EQ(*(current->data), val);
        current = current->next;
    }
}

TEST(BubbleSortTest, ReversedList) {
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(1);

    bubbleSort(list);

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
Compilar con: g++ -std=c++14 -isystem /usr/include/gtest -pthread test_bubblesort.cpp -lgtest -lgtest_main -o test_bubblesort
Ejecutar con: ./test_bubblesort
*/