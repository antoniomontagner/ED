// 2021 antonio
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // exceptions


namespace structures {

template<typename T>
class LinkedList {
 public:
    LinkedList();

    ~LinkedList();

    void clear();

    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem
    T& at(std::size_t index);  // acessar um elemento na posição index
    T& at(std::size_t index) const;  // acessar um elemento na posição index
    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover específico
    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém
    std::size_t find(const T& data) const;  // posição do dado
    std::size_t size() const;  // tamanho da lista

 public:
    class Node {   // Elemento
     public:
        explicit Node(const T& data):
        data_{data}
        {}

        explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {  // getter próximo
            return next_;
        }

        const Node* next() const {  // getter const próximo
            return next_;
        }

        void next(Node* node) {  // setter próximo
            next_ = node;
        }

     private:
        T data_;  // data_
        Node* next_{nullptr};  // next_
    };

    Node* end() {  // ultimo nodo
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* before_index(std::size_t index) const {  // node anterior
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);  // inserir na posicao

    Node* head{nullptr};  // head
    std::size_t size_{0u};  // size_
};

template<typename T>
LinkedList<T>::LinkedList() {}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void LinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
void LinkedList<T>::push_back(const T& data) {
    try {
        insert(data, size_);
    } catch(std::out_of_range error) {
        throw error;
    }
}

template<typename T>
void LinkedList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("LISTA CHEIA");

    new_node->next(head);
    head = new_node;
    size_++;
}

template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("INDEX INVALIDO");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("LISTA CHEIA!");

        Node* before = before_index(index);
        Node* next = before->next();
        new_node->next(next);
        before->next(new_node);
        size_++;
    }
}

template<typename T>
void LinkedList<T>::insert(const T& data, Node* before) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("LISTA CHEIA!");

    new_node->next(before->next());
    before->next(new_node);
    size_++;
}

template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* atual = head;
        Node* before = head;
        std::size_t pos = size();
        for (auto i = 0u; i < size(); ++i) {
            if (!(data > atual->data())) {
                pos = i;
                break;
            }
            before = atual;
            atual = atual->next();
        }
        pos == 0? push_front(data) : insert(data, before);
    }
}

template<typename T>
T& LinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("INVALIDO!");

    Node* atual = index == 0? head : before_index(index)->next();
    return atual->data();
}

template<typename T>
T& LinkedList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("INVALIDO!");

    Node* atual = index == 0? head : before_index(index)->next();
    return atual->data();
}

template<typename T>
T LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("LISTA VAZIA");
    if (index >= size())
        throw std::out_of_range("INDEX INVALIDO");

    if (index == 0)
        return pop_front();

    Node* before_out = before_index(index);
    Node* out = before_out->next();
    T data = out->data();
    before_out->next(out->next());
    size_--;
    delete out;
    return data;
}

template<typename T>
T LinkedList<T>::pop_back() {
    try {
        return pop(size_ - 1u);
    } catch(std::out_of_range error) {
        throw error;
    }
}

template<typename T>
T LinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("LISTA VAZIA");

    auto out = head;
    T data = out->data();
    head = out->next();
    size_--;
    delete out;
    return data;
}

template<typename T>
void LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool LinkedList<T>::empty() const {
    return size() == 0u;
}

template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
std::size_t LinkedList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* atual = head;
    while (index < size()) {
        if (atual->data() == data)
            break;
        atual = atual->next();
        index++;
    }
    return index;
}

template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
