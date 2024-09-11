#include "MPointerGC.h"

MPointerGC* MPointerGC::instance = nullptr;

MPointerGC::MPointerGC() : head(nullptr), id_counter(0) {}

MPointerGC& MPointerGC::GetInstance() {
    if (!instance) {
        instance = new MPointerGC();
        instance->StartGarbageCollector();
    }
    return *instance;
}

int MPointerGC::RegisterPointer(void* mpointer, std::function<void(void*)> deleter, DataType type) {
    std::lock_guard<std::mutex> lock(mtx);
    int id = ++id_counter;
    Node* newNode = new Node(id, mpointer, deleter, type);  // Registrar con tipo de dato
    newNode->next = head;
    head = newNode;
    return id;
}

void MPointerGC::DeregisterPointer(int id) {
    if (id == -1) {
        std::cout << "Pointer with invalid ID (-1), skipping deregistration." << std::endl;
        return;
    }

    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->id == id) {
            current->ref_count--;

            if (current->ref_count == 0) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }

                std::cout << "ID: " << current->id << " ref_count reached 0, deleting..." << std::endl;
                current->deleter(current->ptr);  // Eliminar el puntero
                delete current;
            } else {
                std::cout << "ID: " << id << " ref_count decremented to " << current->ref_count << std::endl;
            }
            return;
        }
        previous = current;
        current = current->next;
    }

    std::cout << "Pointer with ID " << id << " not found in the list." << std::endl;
}

void MPointerGC::IncrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;

    while (current) {
        if (current->id == id) {
            current->ref_count++;
            break;
        }
        current = current->next;
    }
}

void MPointerGC::DecrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;

    while (current) {
        if (current->id == id) {
            current->ref_count--;
            if (current->ref_count == 0) {
                DeregisterPointer(id);
            }
            break;
        }
        current = current->next;
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
    std::cout << "Collecting garbage..." << std::endl;

    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->ref_count == 0) {
            std::cout << "ID: " << current->id << " has ref_count 0 and will be deleted." << std::endl;
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            current->deleter(current->ptr);
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        } else {
            previous = current;
            current = current->next;
        }
    }

    std::cout << "Garbage collection cycle completed." << std::endl;
}

void MPointerGC::debug() {
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;

    std::cout << "=== Memory Debug Info ===" << std::endl;

    if (!current) {
        std::cout << "No pointers are currently registered." << std::endl;
    } else {
        while (current) {
            std::cout << "ID: " << current->id
                      << ", Address: " << current->ptr
                      << ", RefCount: " << current->ref_count;

            // Imprimir valor según el tipo de dato
            switch (current->type) {
                case DataType::INT:
                    std::cout << ", Value: " << *static_cast<int*>(current->ptr);
                    break;
                case DataType::BOOL:
                    std::cout << ", Value: " << (*static_cast<bool*>(current->ptr) ? "true" : "false");
                    break;
                case DataType::FLOAT:
                    std::cout << ", Value: " << *static_cast<float*>(current->ptr);
                    break;
                case DataType::DOUBLE:
                    std::cout << ", Value: " << *static_cast<double*>(current->ptr);
                    break;
                default:
                    std::cout << ", Value: <non-displayable>";
                    break;
            }

            std::cout << std::endl;
            current = current->next;
        }
    }

    std::cout << "=== End of Debug Info ===" << std::endl;
}

int MPointerGC::GetRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;

    while (current) {
        if (current->id == id) {
            return current->ref_count;
        }
        current = current->next;
    }

    return -1;
}
