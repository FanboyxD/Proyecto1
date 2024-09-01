#include "MPointer.hpp"

int main() {
    MPointer<int> ptr1(new int(10));
    MPointer<int> ptr2 = ptr1;

    std::cout << "Value: " << *ptr1 << std::endl;
    std::cout << "Reference Count: " << ptr1.getReferenceCount() << std::endl;

    MPointerGC::getInstance().collectGarbage();

    return 0;
}
