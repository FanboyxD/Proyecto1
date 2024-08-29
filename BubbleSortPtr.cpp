#include "MPointer.h"
#include <iostream>

template <typename T>
class Node {
public:
    MPointer<T> data;
    MPointer<Node<T>> next;
    MPointer<Node<T>> prev;

    Node() : data(MPointer<T>::New()), next(nullptr), prev(nullptr) {}
    Node(T value) : data(MPointer<T>::New()), next(nullptr), prev(nullptr) {
        *data = value;
    }
};

template <typename T>
class DoublyLinkedList {
public:
    MPointer<Node<T>> head;
    MPointer<Node<T>> tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(T value) {
        MPointer<Node<T>> newNode = MPointer<Node<T>>::New();
        newNode->data = MPointer<T>::New();
        *(newNode->data) = value;
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void bubbleSort() {
        if (!head) return;

        bool swapped;
        MPointer<Node<T>> current;
        MPointer<Node<T>> lastSorted = nullptr;

        do {
            swapped = false;
            current = head;

            while (current->next != lastSorted) {
                if (*(current->data) > *(current->next->data)) {
                    std::swap(*(current->data), *(current->next->data));
                    swapped = true;
                }
                current = current->next;
            }
            lastSorted = current;
        } while (swapped);
    }

    void printList() const {
        MPointer<Node<T>> temp = head;
        while (temp != nullptr) {
            std::cout << *(temp->data) << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);
    std::cout << "Lista original: ";
    list.printList();

    list.bubbleSort();

    std::cout << "Lista ordenada: ";
    list.printList();

    return 0;
}
