cmake_minimum_required(VERSION 3.28)
project(MPointer)

set(CMAKE_CXX_STANDARD 17)

# Añadir el directorio de los headers
include_directories(include)

# Agregar Google Test al proyecto
add_subdirectory(googletest)  # Esta línea debe ir antes de definir targets que dependan de Google Test

# Habilitar pruebas en CMake
enable_testing()

# Incluir los headers de Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Crear una biblioteca estática con los archivos .cpp
add_library(MPointerLib STATIC
        src/MPointerGC.cpp
)

# Crear el ejecutable principal
add_executable(MPointer src/main.cpp
        include/Lista/DoublyLinkedList.h
        include/Lista/Node.h
        include/Lista/DoublyLinkedList.tpp
        include/Ordenar/QuickSort.tpp
        include/Ordenar/QuickSort.h
        include/Ordenar/BubbleSort.tpp
        include/Ordenar/BubbleSort.h
        include/Ordenar/InsertionSort.tpp
        include/Ordenar/InsertionSort.h
)

# Enlazar la biblioteca estática con el ejecutable principal
target_link_libraries(MPointer MPointerLib)

# Crear ejecutable de prueba
add_executable(MPointerTests tests/mpointer_tests.cpp)

# Enlazar Google Test y la biblioteca estática al ejecutable de pruebas
target_link_libraries(MPointerTests gtest gtest_main MPointerLib)

# Agregar las pruebas para que CTest las conozca
include(GoogleTest)
gtest_discover_tests(MPointerTests)