#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <cstdlib> // Para malloc y free

template <typename T>
class MPointer;
class QuickSortGtest_Friend;
class MPointerGC {
public:
    static MPointerGC& Instance() {
        static MPointerGC instance;
        return instance;
    }

    template <typename T>
    size_t RegisterMPointer(const MPointer<T>& myPtr) {
        std::lock_guard<std::mutex> lock(mtx);
        size_t id = next_id++; // Genera un ID autogenerado único
        pointers.emplace_back(id, myPtr.ptr);
        return id;
    }

    public:
    size_t GetPointerCount(){
        std::lock_guard<std::mutex> lock(mtx);
        return pointers.size();
    }

    template <typename T>
    void UnregisterMPointer(size_t id) {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.remove_if([id](const auto& pair) { return pair.first == id; });
    }

    void GarbageCollect() {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto it = pointers.begin(); it != pointers.end();) {
            if (it->second == nullptr) {
                it = pointers.erase(it);
            } else {
                ++it;
            }
        }
    }

private:
    MPointerGC() : next_id(0) {
        gc_thread = std::thread([this]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                GarbageCollect();
            }
        });
    }

    ~MPointerGC() {
        running = false;
        if (gc_thread.joinable()) {
            gc_thread.join();
        }
    }

    std::list<std::pair<size_t, void*>> pointers; // Lista enlazada para almacenar las direcciones de memoria
    size_t next_id;
    std::mutex mtx;
    std::thread gc_thread;
    bool running = true;
};

template <typename T>
class MPointer {
public:
    // Constructor por defecto
    MPointer() : ptr(nullptr), id(0), ref_count(static_cast<size_t*>(malloc(sizeof(size_t)))) {
        *ref_count = 1;
    }

    // Constructor que acepta nullptr
    MPointer(std::nullptr_t) : ptr(nullptr), id(0), ref_count(static_cast<size_t*>(malloc(sizeof(size_t)))) {
        *ref_count = 1;
    }
    
    // Constructor de copia
    MPointer(const MPointer<T>& other) 
        : ptr(other.ptr), id(other.id), ref_count(other.ref_count) {
        if (ref_count) {
            ++(*ref_count);
        }
        
    }

    static MPointer<T> New() {
        MPointer<T> myPtr;
        myPtr.ptr = new T(); // Use new instead of malloc
        *(myPtr.ref_count) = 1;
        myPtr.id = MPointerGC::Instance().RegisterMPointer(myPtr);
        return myPtr;
    }

    // Destructor
    ~MPointer() {
        if (ref_count && --(*ref_count) == 0) {
            
            delete ptr; // Use delete instead of free
            free(ref_count); // Use free for ref_count as it was allocated with malloc
            MPointerGC::Instance().UnregisterMPointer<T>(id);
        } else {
            
        }
    }



    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

   // Operador de asignación
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            if (ref_count && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
                MPointerGC::Instance().UnregisterMPointer<T>(id);
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            id = other.id;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }

    MPointer<T>& operator=(T value) {
        *ptr = value;
        return *this;
    }

    T& operator&() {
        return *ptr;
    }

    // Sobrecarga del operador !
    bool operator!() const {
        return ptr == nullptr;
    }

    // Sobrecarga del operador ==
    bool operator==(const MPointer<T>& other) const {
        return ptr == other.ptr;
    }

    // Sobrecarga del operador !=
    bool operator!=(const MPointer<T>& other) const {
        return ptr != other.ptr;
    }

    operator bool() const {
        return ptr != nullptr;
    }
private:
    T* ptr;
    size_t id;
    size_t* ref_count;

    friend class MPointerGC;
};
