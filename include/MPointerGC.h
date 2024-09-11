#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <functional>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

// Enumeración para los tipos de datos
enum class DataType {
    INT,
    BOOL,
    FLOAT,
    DOUBLE,
    UNKNOWN
};

class MPointerGC {
private:
    struct Node {
        int id;
        void* ptr;
        std::function<void(void*)> deleter;
        int ref_count;
        Node* next;
        DataType type;  // Tipo de dato

        Node(int i, void* p, std::function<void(void*)> d, DataType t)
            : id(i), ptr(p), deleter(d), ref_count(1), next(nullptr), type(t) {}
    };

    Node* head;
    std::mutex mtx;
    static MPointerGC* instance;
    int id_counter;

    MPointerGC();

public:
    static MPointerGC& GetInstance();

    int RegisterPointer(void* mpointer, std::function<void(void*)> deleter, DataType type);  // Registrar con tipo de dato
    void DeregisterPointer(int id);
    void IncrementRefCount(int id);
    void DecrementRefCount(int id);

    void StartGarbageCollector();
    void CollectGarbage();
    void debug();
    int GetRefCount(int id);
};

#endif // MPOINTERGC_H
