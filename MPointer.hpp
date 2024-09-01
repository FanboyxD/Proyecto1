#ifndef MPOINTER_HPP
#define MPOINTER_HPP

#include <iostream>
#include <unordered_map>
#include <memory>

template<typename T>
class MPointer;

class MPointerGC {
public:
    static MPointerGC& getInstance() {
        static MPointerGC instance;
        return instance;
    }

    template<typename T>
    void registerPointer(MPointer<T>* ptr);

    template<typename T>
    void unregisterPointer(MPointer<T>* ptr);

    int getReferenceCount(void* ptr) const;

    void collectGarbage();

private:
    std::unordered_map<void*, int> referenceCount;

    MPointerGC() = default;
    ~MPointerGC() = default;
};

template<typename T>
class MPointer {
public:
    MPointer();
    explicit MPointer(T* ptr);
    ~MPointer();

    MPointer(const MPointer<T>& other);
    MPointer& operator=(const MPointer<T>& other);

    T& operator*();
    T* operator->();
    T* getPointer() const;

    int getReferenceCount() const;

private:
    T* ptr;
    void registerThisPointer();
    void unregisterThisPointer();
};

#include "MPointer.tpp"

#endif // MPOINTER_HPP
