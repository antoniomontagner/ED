// 2021 antonio
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // exceptions
#include "./linked_list.h"

namespace structures {

template<typename T>
class LinkedStack : private LinkedList<T> {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo
    
    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha
};

template<typename T>
LinkedStack<T>::LinkedStack() : LinkedList<T>::LinkedList() {}

template<typename T>
LinkedStack<T>::~LinkedStack() {
  LinkedList<T>::~LinkedList();
}

template<typename T>
void LinkedStack<T>::clear() {
  LinkedList<T>::clear();
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
    LinkedList<T>::push_front(data);
}

template<typename T>
T LinkedStack<T>::pop() {
    return LinkedList<T>::pop_front();
}

template<typename T>
T& LinkedStack<T>::top() const {
    return LinkedList<T>::at(0u);
}

template<typename T>
bool LinkedStack<T>::empty() const {
  return LinkedList<T>::empty();
}

template<typename T>
size_t LinkedStack<T>::size() const {
  return LinkedList<T>::size();
}

}  // namespace structures

#endif