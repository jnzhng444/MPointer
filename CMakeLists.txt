cmake_minimum_required(VERSION 3.28)
project(MPointer)

set(CMAKE_CXX_STANDARD 17)

# Añadir el directorio de los headers
include_directories(include)

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

# Enlazar la biblioteca estática con el ejecutable
target_link_libraries(MPointer MPointerLib)
