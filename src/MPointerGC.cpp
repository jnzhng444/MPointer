#include "MPointerGC.h"
#include <iostream>

MPointerGC* MPointerGC::instance = nullptr;

MPointerGC::MPointerGC() {}

MPointerGC& MPointerGC::GetInstance() {
    if (!instance) {
        instance = new MPointerGC();
    }
    return *instance;
}

int MPointerGC::RegisterPointer(void* mpointer, std::function<void(void*)> deleter) {
    std::lock_guard<std::mutex> lock(mtx);
    static int id_counter = 0;
    pointers[++id_counter] = std::make_pair(mpointer, deleter);
    return id_counter;
}

void MPointerGC::DeregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = pointers.find(id);
    if (it != pointers.end()) {
        it->second.second(it->second.first);  // Llama a la función de eliminación
        pointers.erase(it);  // Elimina del mapa
    }
}

void MPointerGC::IncrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    // Aquí podrías implementar un contador de referencias si fuera necesario.
}

void MPointerGC::DecrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    // Aquí podrías implementar la lógica para reducir el contador de referencias.
}

void MPointerGC::StartGarbageCollector() {
    std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            CollectGarbage();
        }
    }).detach();
}

void MPointerGC::CollectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = pointers.begin(); it != pointers.end();) {
        // Aquí podrías implementar lógica para liberar memoria si fuera necesario.
        ++it;
    }
}
