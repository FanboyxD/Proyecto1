// BubbleSort.cpp
#include "DoublyLinkedList.h"

template <typename T>
void bubbleSort(DoublyLinkedList<T>& list) {
    if (!list.head) return;

    bool swapped;
    MPointer<Node<T>> current;
    MPointer<Node<T>> lastSorted = nullptr;

    do {
        swapped = false;
        current = list.head;

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

int main() {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);
    std::cout << "Lista original: ";
    list.printList();

    bubbleSort(list);

    std::cout << "Lista ordenada con Bubble Sort: ";
    list.printList();

    return 0;
}
