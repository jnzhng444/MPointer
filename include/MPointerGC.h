#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <mutex>

class MPointerBase {
public:
    virtual ~MPointerBase() = default;
};

class MPointerGC {
private:
    struct MPointerInfo {
        MPointerBase* mpointer;
        int refCount;
    };

    std::unordered_map<int, MPointerInfo> pointersMap;
    int nextId;
    std::mutex mtx;
    bool gcRunning; // Flag to indicate if GC is running

    MPointerGC();

public:
    static MPointerGC* getInstance();

    int registerPointer(MPointerBase* mpointer);
    void unregisterPointer(int id);
    void increaseRefCount(int id);
    void startGC();
    void stopGC(); // Method to stop GC

private:
    void collectGarbage();
};

#endif
