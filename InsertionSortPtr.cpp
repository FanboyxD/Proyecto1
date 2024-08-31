// InsertionSort.cpp
#include "DoublyLinkedList.h"

template <typename T>
void insertionSort(DoublyLinkedList<T>& list) {
    if (!list.head) return;

    MPointer<Node<T>> sorted = nullptr;
    MPointer<Node<T>> current = list.head;

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

    list.head = sorted;

    // Update tail
    list.tail = list.head;
    while (list.tail->next != nullptr) {
        list.tail = list.tail->next;
    }
}

int main() {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);
    std::cout << "Lista original: ";
    list.printList();

    insertionSort(list);

    std::cout << "Lista ordenada con Insertion Sort: ";
    list.printList();

    return 0;
}
