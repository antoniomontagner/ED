//!  Copyright [2021] <antonio s m>
//
// Implementação de Lista Duplamente Encadeada
//
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>

class DoublyLinkedList {
 public:
    DoublyLinkedList() {}

    ~DoublyLinkedList() {
        clear();
    }

    void clear() {
        while (!empty())
           pop_front();
    }

    void push_back(const T& data) {  //  insere no fim
        insert(data, size_);
    }

    void push_front(const T& data) {  // insere no início
        Node *novo;
        novo = new Node(data);
        if (novo == nullptr)
            throw std::out_of_range("LISTA CHEIA!!!");
        if (empty()) {
            head = novo;
        } else {
            novo -> next(head);
            head -> prev(novo);
            head = novo;
        }
        size_++;
    }

    void insert(const T& data, std::size_t index) {  //  insere na posição
        if (index > size_)
            throw std::out_of_range("ERRO NA POSIÇÃO!!!");
        if (index == 0) {
            push_front(data);
        } else {
            Node *novo;
            novo = new Node(data);
            if (novo == nullptr)
                throw std::out_of_range("LISTA CHEIA!!!");
            if (index == size_) {
                Node *atual = end();
                atual -> next(novo);
                novo -> prev(atual);
            } else {
                Node *atual = pegar_index(index);
                novo -> next(atual);
                novo -> prev(atual -> prev());
                atual -> prev() -> next(novo);
                atual -> prev(novo);
            }
        size_++;
        }
    }

    void insert_sorted(const T& data) {  //  insere em ordem
        if (empty()) {
            push_front(data);
        } else {
            Node *atual;
            std::size_t posicao;
            atual = head;
            posicao = 0;
            while (atual -> next() != NULL && data > atual -> data()) {
                atual = atual -> next();
                posicao++;
            }
            if (posicao ==0) {
                push_front(data);
            } else {
                Node *novo = new Node(data);
                if (data > atual -> data()) {
                    atual -> next(novo);
                    novo -> prev(atual);
                } else {
                    novo ->prev(atual->prev());
                    novo -> next(atual);
                    atual -> prev() -> next(novo);
                    atual -> prev(novo);
                }
                size_++;
            }
        }
    }

    T pop(std::size_t index) {  //  retira da posição
        if (empty())
            throw std::out_of_range("LISTA VAZIA!!!");
        if (index >= size())
            throw std::out_of_range("ERRO NA POSIÇÃO!!!");
        if (index == 0)
            return pop_front();
        Node *anterior = pegar_index(index);
        T data = anterior -> data();
        anterior -> prev() -> next(anterior -> next());
        if (anterior -> next() != nullptr)
            anterior -> next() -> prev(anterior -> prev());
        size_--;
        delete anterior;
        return data;
    }

    T pop_back()  {  //  retira do fim
        return pop(size_ - 1u);
    }

    T pop_front() {  //  retira do início
         if (empty())
            throw std::out_of_range("LISTA VAZIA!!!");
        Node * atual = head;
        T volta = atual -> data();
        head = atual -> next();
        if (head != nullptr)
             head -> prev(nullptr);
        size_--;
        delete atual;
        return volta;
    }

    void remove(const T& data) {  //  retira específico
        pop(find(data));
    }

    bool empty() const {  //  lista vazia
        return size() == 0u;
    }

    bool contains(const T& data) const {  //  contém
        return find(data) != size_;
    }

    T& at(std::size_t index) {  //   acesso a um elemento (checando limites)
        if (index >= size())
            throw std::out_of_range("POSIÇÃO INVÁLIDA!!!");
        auto posicao = index == 0?
        head:pegar_index(index);
        return posicao->data();
    }

    const T& at(std::size_t index) const {  //  getter constante a um elemento
        if (index >= size())
            throw std::out_of_range("POSIÇÃO INVÁLIDA!!!");
        auto posicao = index == 0?
        head:pegar_index(index);
        return posicao->data();
    }

    std::size_t find(const T& data) const {  //  posição de um dado
        std::size_t temp = 0;
        Node *posicao = head;
        while (temp < size()) {
            if (posicao->data() == data)
                break;
            posicao = posicao->next();
            temp++;
           }
        return temp;
    }

    std::size_t size() const {  //  tamanho
        return size_;
    }

 private :
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private :
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};    // primeiro da lista
    std::size_t size_{0u};

    Node* end() {  //  último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
           it = it->next();
        }
        return it;
    }

    Node* pegar_index(std::size_t index) {  //  último nodo da lista(posição)
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
           it = it->next();
        }
        return it;
    }
};
}  // namespace structures

#endif  //  STRUCTURES_DOUBLY_LINKED_LIST_H
