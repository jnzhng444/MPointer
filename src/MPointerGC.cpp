// MPointerGC.cpp

#include "../include/MPointerGC.h"
#include <thread>
#include <chrono>

MPointerGC* MPointerGC::getInstance() {
    static MPointerGC instance;
    return &instance;
}

MPointerGC::MPointerGC() : nextId(0) {}

int MPointerGC::registerPointer(MPointerBase* mpointer) {
    std::lock_guard<std::mutex> lock(mtx);
    int id = nextId++;
    pointersMap[id] = {mpointer, 1};
    return id;
}

void MPointerGC::unregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = pointersMap.find(id);
    if (it != pointersMap.end()) {
        it->second.refCount--;
        if (it->second.refCount <= 0) {
            delete it->second.mpointer;
            pointersMap.erase(it);
        }
    }
}

void MPointerGC::increaseRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    pointersMap[id].refCount++;
}

void MPointerGC::startGC() {
    std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            this->collectGarbage();
        }
    }).detach();
}

void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = pointersMap.begin(); it != pointersMap.end(); ) {
        if (it->second.refCount <= 0) {
            delete it->second.mpointer;
            it = pointersMap.erase(it);
        } else {
            ++it;
        }
    }
}
