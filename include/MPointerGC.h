#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <mutex>
#include <thread>
#include <chrono>

class MPointerGC {
private:
    std::unordered_map<int, std::pair<void*, int>> pointers; // ID -> (pointer, ref_count)
    std::mutex mtx;
    static MPointerGC* instance;

    MPointerGC();

public:
    static MPointerGC& GetInstance();

    int RegisterPointer(void* mpointer);
    void DeregisterPointer(int id);
    void IncrementRefCount(int id);
    void DecrementRefCount(int id);

    void StartGarbageCollector();
    void CollectGarbage();
};

#endif // MPOINTERGC_H
