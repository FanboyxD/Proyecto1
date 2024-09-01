// QuickSort.cpp
#include "DoublyLinkedList.h"

template <typename T>
MPointer<Node<T>> partition(MPointer<Node<T>> low, MPointer<Node<T>> high) {
    if (!low || !high || !high->data) return low;
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

template <typename T>
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

/* int main() {
    DoublyLinkedList<int> list;
    list.append(4);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);
    std::cout << "Lista original: ";
    list.printList();

    quicksort(list.head, list.tail);

    std::cout << "Lista ordenada con Quicksort: ";
    list.printList();

    return 0;
} */
