#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <mutex>
#include <thread>
#include <chrono>
#include <functional>

class MPointerGC {
private:
    std::unordered_map<int, std::pair<void*, std::function<void(void*)>>> pointers;  // ID -> (puntero, función de eliminación)
    std::unordered_map<int, int> ref_counts;  // ID -> contador de referencias
    std::mutex mtx;
    static MPointerGC* instance;

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
