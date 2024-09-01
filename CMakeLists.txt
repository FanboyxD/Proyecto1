cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Proyecto1)

# Configuración de Google Test
add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

include_directories(${PROJECT_SOURCE_DIR}/googletest/googletest/include)

# Agregar los archivos de prueba
add_executable(test_quick_sort ../test_quick_sort.cpp)
add_executable(test_insertion_sort ../test_insertion_sort.cpp)
add_executable(test_bubble_sort ../test_bubble_sort.cpp)
add_executable(test_doubly_linked_list ../test_doubly_linked_list.cpp)
add_executable(test_mpointer ../test_mpointer.cpp)


# Enlazar con Google Test
target_link_libraries(test_quick_sort gtest gtest_main pthread)
target_link_libraries(test_insertion_sort gtest gtest_main pthread)
target_link_libraries(test_bubble_sort gtest gtest_main pthread)
target_link_libraries(test_doubly_linked_list gtest gtest_main pthread)
target_link_libraries(test_mpointer gtest gtest_main pthread)