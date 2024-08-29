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

    void insertionSort() {
        if (!head) return;

        MPointer<Node<T>> sorted = nullptr;
        MPointer<Node<T>> current = head;

        while (current != nullptr) {
            MPointer<Node<T>> next = current->next;

            if (!sorted || *(sorted->data) >= *(current->data)) {
                current->next = sorted;
                if (sorted) sorted->prev = current;
                sorted = current;
                sorted->prev = nullptr;
            } else {
                MPointer<Node<T>> temp = sorted;
                while (temp->next != nullptr && *(temp->next->data) < *(current->data)) {
                    temp = temp->next;
                }

                current->next = temp->next;
                if (temp->next != nullptr) {
                    temp->next->prev = current;
                }
                temp->next = current;
                current->prev = temp;
            }
            current = next;
        }

        head = sorted;

        // Update tail
        tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
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

    list.insertionSort();

    std::cout << "Lista ordenada: ";
    list.printList();

    return 0;
}
