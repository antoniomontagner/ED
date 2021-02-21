// Copyright [2021] <Antonio S Montagner>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
 public:
    ArrayQueue();  // construtor padrão
    explicit ArrayQueue(std::size_t max);  //! construtor com parametro
    ~ArrayQueue();  //! destrutor padrao
    void enqueue(const T &data);  //! metodo enfileirar
    T dequeue();  //! metodo desenfileirar
    T& back();  //! metodo retorna o ultimo
    void clear();  //! metodo limpa a fila
    std::size_t size();  //! metodo retorna tamanho atual
    std::size_t max_size();  //! metodo retorna tamanho maximo
    bool empty();  //! metodo verifica se vazio
    bool full();  //! metodo verifica se esta cheio

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular) // take_idx
    int end_;  // indice do fim (para fila circular) // put_idx
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    contents = new T[DEFAULT_SIZE];
    begin_ = size_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max];
    begin_ = size_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T &data) {
    if (full()) {
        throw std::out_of_range("fila esta cheia");
    } else {
        end_ = ((end_ + 1) % max_size_);
        contents[end_] = data;
        size_++;
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila esta vazia");
    } else {
        T old_value = contents[begin_];
        begin_ = ((begin_ + 1) % max_size_);
        size_--;
        return old_value;
    }
}

template<typename T>
T &structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila esta vazia");
    } else {
        return contents[end_];
    }
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    begin_ = size_ = 0;
    end_ = -1;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return (size_ == 0);
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return (size_ == max_size_);
}
