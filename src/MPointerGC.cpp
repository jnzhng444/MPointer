#include "MPointerGC.h"

MPointerGC* MPointerGC::instance = nullptr;

MPointerGC::MPointerGC() : head(nullptr), id_counter(0) {
    // Constructor vacío
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
    int id = ++id_counter;
    Node* newNode = new Node(id, mpointer, deleter);
    newNode->next = head;
    head = newNode;
    return id;
}

void MPointerGC::DeregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->id == id) {
            current->ref_count--;  // Decrementar el contador de referencias
            if (current->ref_count == 0) {
                std::cout << "ID: " << current->id << " ref_count is 0, pointer will be deleted." << std::endl;
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                current->deleter(current->ptr);
                delete current;
            } else {
                std::cout << "ID: " << current->id << " ref_count decremented to " << current->ref_count << std::endl;
            }
            break;
        }
        previous = current;
        current = current->next;
    }
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
                DeregisterPointer(id);  // Eliminar el puntero si el contador llega a cero
            }
            break;
        }
        current = current->next;
    }
}

void MPointerGC::StartGarbageCollector() {
    std::thread([this]() {
        while (true) {  // Bucle infinito para la recolección continua de basura
            std::this_thread::sleep_for(std::chrono::seconds(5));  // Espera 5 segundos entre colecciones
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
        if (current->ref_count == 0) {  // Verificar si el puntero debe ser eliminado
            std::cout << "ID: " << current->id << " has ref_count 0 and will be deleted." << std::endl; // Imprimir antes de eliminar
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
                      << ", RefCount: " << current->ref_count
                      << std::endl;
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
            return current->ref_count;  // Retornar el contador de referencias
        }
        current = current->next;
    }

    return -1;  // Si no se encuentra el ID, retornar -1 (indicando un error)
}

