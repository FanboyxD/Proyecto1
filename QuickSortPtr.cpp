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

    MPointer<Node<T>> partition(MPointer<Node<T>> low, MPointer<Node<T>> high) {
        if (!low || !high || !high->data) return low; // Additional null check
        T pivot = *(high->data);
        MPointer<Node<T>> i = low->prev;
        for (MPointer<Node<T>> j = low; j != high && j != nullptr; j = j->next) {
            if (j->data && *(j->data) <= pivot) {
                i = (i == nullptr) ? low : i->next;
                if (i && i->data && j->data) {
                    std::swap(*(i->data), *(j->data));
                }
            }
        }
        i = (i == nullptr) ? low : i->next;
        if (i && i->data && high->data) {
            std::swap(*(i->data), *(high->data));
        }
        return i;
    }

    void quicksort(MPointer<Node<T>> low, MPointer<Node<T>> high) {
        if (!low || !high || low == high || low == high->next) return;
        MPointer<Node<T>> p = partition(low, high);
        if (p && p->prev && p->prev != low) {
            quicksort(low, p->prev);
        }
        if (p && p->next && p->next != high) {
            quicksort(p->next, high);
        }
    }

    void printList() const {
        MPointer<Node<T>> temp = head;
        while (temp != nullptr) { // Comparación explícita con nullptr
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
    list.quicksort(list.head, list.tail);
    std::cout << "Lista ordenada: ";
    list.printList();
    return 0;
}
