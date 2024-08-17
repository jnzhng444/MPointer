#ifndef DOUBLYLINKEDLIST_TPP
#define DOUBLYLINKEDLIST_TPP

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::append(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    size++;
}

template <typename T>
void DoublyLinkedList<T>::prepend(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (head) {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    } else {
        head = tail = newNode;
    }
    size++;
}

template <typename T>
void DoublyLinkedList<T>::remove(Node<T>* node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (node == head) head = node->next;
    if (node == tail) tail = node->prev;
    delete node;
    size--;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getHead() const {
    return head;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getTail() const {
    return tail;
}

#endif // DOUBLYLINKEDLIST_TPP
