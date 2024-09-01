#include "gtest/gtest.h"
#include "MPointer.h"

// Caso de prueba para el constructor por defecto
// Caso de prueba para el constructor por defecto
TEST(MPointerTest, DefaultConstructor) {
    MPointer<int> ptr;
    EXPECT_TRUE(!ptr);  // Verifica que el puntero esté inicialmente nulo
}


// Caso de prueba para la función New
TEST(MPointerTest, NewFunction) {
    MPointer<int> ptr = MPointer<int>::New();
    *ptr = 5;
    EXPECT_EQ(*ptr, 5);  // Espera que el valor sea 5
    EXPECT_FALSE(!ptr);  // Espera que el puntero no sea nulo
}

// Caso de prueba para el constructor de copia
TEST(MPointerTest, CopyConstructor) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 10;
    MPointer<int> ptr2(ptr1);
    EXPECT_EQ(*ptr2, 10);  // Espera que el valor sea el mismo que en ptr1
    EXPECT_FALSE(!ptr2);   // Espera que el puntero no sea nulo
}

// Caso de prueba para el operador de asignación
TEST(MPointerTest, AssignmentOperator) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 20;
    MPointer<int> ptr2 = ptr1;
    EXPECT_EQ(*ptr2, 20);  // Espera que el valor sea 20
    EXPECT_FALSE(!ptr2);   // Espera que el puntero no sea nulo
}

// Caso de prueba para el operador de acceso al valor
TEST(MPointerTest, DereferenceOperator) {
    MPointer<int> ptr = MPointer<int>::New();
    *ptr = 30;
    EXPECT_EQ(*ptr, 30);  // Espera que el valor sea 30
}

// Caso de prueba para el operador flecha
TEST(MPointerTest, ArrowOperator) {
    struct TestStruct {
        int x;
        int y;
    };
    MPointer<TestStruct> ptr = MPointer<TestStruct>::New();
    ptr->x = 40;
    ptr->y = 50;
    EXPECT_EQ(ptr->x, 40);  // Espera que el valor de x sea 40
    EXPECT_EQ(ptr->y, 50);  // Espera que el valor de y sea 50
}

// Caso de prueba para el Garbage Collector
TEST(MPointerTest, GarbageCollector) {
    size_t initial_count = MPointerGC::Instance().GetPointerCount();
    {
        MPointer<int> ptr = MPointer<int>::New();
        EXPECT_EQ(MPointerGC::Instance().GetPointerCount(), initial_count + 1);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Espera a que el Garbage Collector ejecute
    EXPECT_EQ(MPointerGC::Instance().GetPointerCount(), initial_count);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
