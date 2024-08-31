// DoublyLinkedList.h
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

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

    void printList() const {
        MPointer<Node<T>> temp = head;
        while (temp != nullptr) {
            std::cout << *(temp->data) << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

#endif // DOUBLYLINKEDLIST_H
