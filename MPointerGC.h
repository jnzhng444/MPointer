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

    MPointerGC();

public:
    static MPointerGC* getInstance();

    int registerPointer(MPointerBase* mpointer);
    void unregisterPointer(int id);
    void increaseRefCount(int id);
    void startGC();

private:
    void collectGarbage();
};

#endif
