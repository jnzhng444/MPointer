#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <functional>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

class MPointerGC {
private:
    struct Node {
        int id;
        void* ptr;
        std::function<void(void*)> deleter;
        int ref_count;  // Contador de referencias
        Node* next;

        Node(int i, void* p, std::function<void(void*)> d) : id(i), ptr(p), deleter(d), ref_count(1), next(nullptr) {}
    };


    Node* head;  // Cabeza de la lista enlazada
    std::mutex mtx;
    static MPointerGC* instance;
    int id_counter;

    MPointerGC();  // Constructor privado

public:
    static MPointerGC& GetInstance();

    int RegisterPointer(void* mpointer, std::function<void(void*)> deleter);  // Registrar un nuevo puntero
    void DeregisterPointer(int id);  // Eliminar un puntero registrado
    void IncrementRefCount(int id);  // Incrementar el contador de referencias
    void DecrementRefCount(int id);  // Decrementar el contador de referencias

    void StartGarbageCollector();  // Iniciar el garbage collector
    void CollectGarbage();  // Recolectar basura
};

#endif // MPOINTERGC_H
