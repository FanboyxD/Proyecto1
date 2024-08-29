#include "MPointer.h"

int main() {
    // Crear un MPointer que gestione un entero
    MPointer<int> myPtr = MPointer<int>::New();
    // Crear otro MPointer
    MPointer<int> myPtr2 = MPointer<int>::New();
    
    // Asignar un valor al MPointer
    *myPtr = 42;

    // Igualar myPtr2 a myPtr
    myPtr2 = myPtr;

    // Imprimir los valores
    std::cout << "Valor de myPtr: " << *myPtr << std::endl;
    std::cout << "Valor de myPtr2: " << *myPtr2 << std::endl;

    myPtr = 6;

    // Usar el operador & para obtener el valor
    int valor = &myPtr;
    std::cout << "Valor de myPtr: " << valor << std::endl;

    return 0;
}
