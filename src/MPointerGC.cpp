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

int MPointerGC::RegisterPointer(void* mpointer) {
    std::lock_guard<std::mutex> lock(mtx);
    static int id_counter = 0;
    pointers[++id_counter] = std::make_pair(mpointer, 1); // Inicia con una referencia
    return id_counter;
}

void MPointerGC::DeregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = pointers.find(id);
    if (it != pointers.end()) {
        if (--(it->second.second) == 0) {
            delete static_cast<int*>(it->second.first); // Libera la memoria
            pointers.erase(it);
        }
    }
}

void MPointerGC::IncrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    pointers[id].second++;
}

void MPointerGC::DecrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (--pointers[id].second == 0) {
        delete static_cast<int*>(pointers[id].first); // Libera la memoria
        pointers.erase(id);
    }
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
        if (it->second.second == 0) { // Si el contador de referencias es 0
            delete static_cast<int*>(it->second.first); // Libera la memoria
            it = pointers.erase(it); // Elimina del mapa
        } else {
            ++it;
        }
    }
}
