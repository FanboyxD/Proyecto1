#include "MPointer.hpp"

template<typename T>
MPointer<T>::MPointer() : ptr(nullptr) {
    registerThisPointer();
}

template<typename T>
MPointer<T>::MPointer(T* ptr) : ptr(ptr) {
    registerThisPointer();
}

template<typename T>
MPointer<T>::~MPointer() {
    unregisterThisPointer();
}

template<typename T>
MPointer<T>::MPointer(const MPointer<T>& other) : ptr(other.ptr) {
    registerThisPointer();
}

template<typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        unregisterThisPointer();
        ptr = other.ptr;
        registerThisPointer();
    }
    return *this;
}

template<typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template<typename T>
T* MPointer<T>::operator->() {
    return ptr;
}

template<typename T>
T* MPointer<T>::getPointer() const {
    return ptr;
}

template<typename T>
int MPointer<T>::getReferenceCount() const {
    return MPointerGC::getInstance().getReferenceCount(ptr);
}

template<typename T>
void MPointer<T>::registerThisPointer() {
    if (ptr) {
        MPointerGC::getInstance().registerPointer(this);
    }
}

template<typename T>
void MPointer<T>::unregisterThisPointer() {
    if (ptr) {
        MPointerGC::getInstance().unregisterPointer(this);
    }
}

template<typename T>
void MPointerGC::registerPointer(MPointer<T>* mpointer) {
    if (mpointer->getPointer()) {
        referenceCount[mpointer->getPointer()]++;
    }
}

template<typename T>
void MPointerGC::unregisterPointer(MPointer<T>* mpointer) {
    if (mpointer->getPointer()) {
        referenceCount[mpointer->getPointer()]--;
        if (referenceCount[mpointer->getPointer()] == 0) {
            delete mpointer->getPointer();
            referenceCount.erase(mpointer->getPointer());
        }
    }
}

int MPointerGC::getReferenceCount(void* ptr) const {
    auto it = referenceCount.find(ptr);
    if (it != referenceCount.end()) {
        return it->second;
    }
    return 0;
}

void MPointerGC::collectGarbage() {
    for (auto it = referenceCount.begin(); it != referenceCount.end(); ) {
        if (it->second == 0) {
            delete static_cast<char*>(it->first);
            it = referenceCount.erase(it);
        } else {
            ++it;
        }
    }
}
