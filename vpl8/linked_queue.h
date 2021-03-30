//!  Copyright [2021] <antonio s m>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"

namespace structures {

template<typename T>

class LinkedQueue : private LinkedList<T> {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();   // limpar

    void enqueue(const T& data);     // enfilerar

    T dequeue();     // desenfilerar

    T& front() const;   // primeiro dado

    T& back() const;    // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;   // tamanho

 private:
    typedef typename LinkedList<T>::Node Node;
    Node* tail{nullptr};  // ultimo node da fila.
};

template<typename T>
LinkedQueue<T>::LinkedQueue() : LinkedList<T>::LinkedList() {}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    LinkedList<T>::clear();
}

template<typename T>
void LinkedQueue<T>::clear() {
    LinkedList<T>::clear();
}

template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    auto new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("FILA CHEIA");

    if (empty()) {
        LinkedList<T>::head = new_node;
        tail = LinkedList<T>::head;
    } else {
        tail->next(new_node);
        tail = new_node;
    }
    LinkedList<T>::size_++;
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    T temp = LinkedList<T>::pop_front();
    if (empty())
        tail = nullptr;
    return temp;
}

template<typename T>
T& LinkedQueue<T>::front() const {
    return LinkedList<T>::at(0u);
}

template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("FILA VAZIA!");
    return tail->data();
}

template<typename T>
bool LinkedQueue<T>::empty() const {
    return LinkedList<T>::empty();
}

template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return LinkedList<T>::size();
}

}  // namespace structures

#endif
