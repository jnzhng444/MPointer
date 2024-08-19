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
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            current->deleter(current->ptr);
            delete current;
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
