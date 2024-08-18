#include "MPointerGC.h"
#include <iostream>

MPointerGC* MPointerGC::instance = nullptr;

MPointerGC::MPointerGC() {
    StartGarbageCollector();  // Iniciar el garbage collector en un thread separado
}


MPointerGC& MPointerGC::GetInstance() {
    if (!instance) {
        instance = new MPointerGC();
        instance->StartGarbageCollector();  // Iniciar el garbage collector
    }
    return *instance;
}

int MPointerGC::RegisterPointer(void* mpointer, std::function<void(void*)> deleter) {
    std::lock_guard<std::mutex> lock(mtx);
    static int id_counter = 0;
    int id = ++id_counter;
    pointers[id] = std::make_pair(mpointer, deleter);
    ref_counts[id] = 1;  // Inicializar contador de referencias en 1
    return id;
}

void MPointerGC::DeregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = pointers.find(id);
    if (it != pointers.end()) {
        it->second.second(it->second.first);  // Llama a la función de eliminación
        pointers.erase(it);  // Elimina del mapa
        ref_counts.erase(id);  // Elimina el contador de referencias
    }
}

void MPointerGC::IncrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (ref_counts.find(id) != ref_counts.end()) {
        ref_counts[id]++;
    }
}

void MPointerGC::DecrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (ref_counts.find(id) != ref_counts.end()) {
        ref_counts[id]--;
        if (ref_counts[id] == 0) {
            DeregisterPointer(id);  // Eliminar el puntero si el contador llega a cero
        }
    }
}

void MPointerGC::StartGarbageCollector() {
    std::thread([this]() {
        int iteration = 0;
        while (iteration < 3) {  // Limitar a 3 iteraciones para pruebas
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Espera 1 segundo entre colecciones
            CollectGarbage();
            iteration++;
        }
    }).detach();
}


void MPointerGC::CollectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Collecting garbage..." << std::endl;

    for (auto it = pointers.begin(); it != pointers.end();) {
        // Aquí podrías implementar lógica para liberar memoria si fuera necesario.
        std::cout << "Pointer ID: " << it->first << " still exists." << std::endl;
        ++it;
    }

    std::cout << "Garbage collection cycle completed." << std::endl;
}

