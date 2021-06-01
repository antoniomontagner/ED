// Copyright [2021] <Anthony Bernardo Kamers>
#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <algorithm>
#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
        }

        T data;
        int height_{0};
        Node* left{nullptr};
        Node* right{nullptr};

        // getter (altura)
        int height(Node *N) {
            if (N == NULL)
                return 0;
            return N->height_;
        }

        Node* simpleLeft(Node *k2) {
            // fazer rotacao
            Node *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;

            // atualizar alturas
            k2->height_ = std::max(height(k2->left),
                                    height(k2->right)) + 1;
            k1->height_ = std::max(height(k1->left),
                                    height(k1->right)) + 1;

            // retorna o nodo rodado
            return k1;
        }

        Node* simpleRight(Node *k2) {
            // fazer rotacao
            Node *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;

            // atualizar alturas
            k2->height_ = std::max(height(k2->left),
                                    height(k2->right)) + 1;
            k1->height_ = std::max(height(k1->left),
                                    height(k1->right)) + 1;

            // retorna o nodo rodado
            return k1;
        }

        Node *doubleLeft(Node *k3) {
            // roda entre k1 e k2
            k3->left = simpleRight(k3->left);

            // roda entre k3 e k2
            return simpleLeft(k3);
        }

        Node *doubleRight(Node *k3) {
            // roda entre k1 e k2
            k3->right = simpleLeft(k3->right);

            // roda entre k3 e k2
            return simpleRight(k3);
        }

        // auxiliar para ter o balanco de rotacao
        int get_balance(Node *node) {
            if (node == NULL)
                return 0;
            return height(node->left) -
                    height(node->right);
        }

        Node* insert(Node* node, const T &data_) {
            // é nulo, somente cria o nodo e retorna
            if (node == NULL) {
                Node* node = new Node(data_);
                return node;
            }

            // testar para qual lado vai o nodo
            if (data_ < node->data)
                // cria a esquerda
                node->left = insert(node->left, data_);
            else if (data_ > node->data)
                // cria a direita
                node->right = insert(node->right, data_);
            else
                throw std::out_of_range("ja existe essa chave na arvore");

            // atualiza altura
            node->height_ = std::max(height(node->left),
                                        height(node->right)) + 1;

            // pegar fator de balanco
            int balance = get_balance(node);

            // casos que necessitam de rotacao
            // esquerda-esquerda
            if (balance > 1 && data_ < node->left->data)
                return simpleLeft(node);

            // direita-direita
            if (balance < -1 && data_ > node->right->data)
                return simpleRight(node);

            // esquerda-direita
            if (balance > 1 && data_ > node->left->data) {
                doubleLeft(node);
            }

            // direita-esquerda
            if (balance < -1 && data_ < node->right->data) {
                doubleRight(node);
            }

            // retorna o nodo sem alteracoes
            return node;
        }

        Node* remove(const T &data_) {
            Node *node = this;

            if (data_ < node->data) {
                // vai para esquerda
                node->left = node->left->remove(data_);

            } else if (data > node->data) {
                // vai para direita
                node->right = node->right->remove(data_);

            } else {
                // esse é o nodo a ser deletado
                if (
                    (node->left == NULL) ||
                    (node->right == NULL)
                ) {
                    // tem somente um filho
                    // verificação de qual filho existe
                    Node *tmp = node->left ?
                                node->left : node->right;

                    // se não há nenhum filho
                    if (tmp == NULL) {
                        tmp = node;
                        node = NULL;
                    } else {
                        *node = *tmp;  // copia os dados
                        delete tmp;
                    }
                } else {
                    // tem dois filhos
                    // recebe o menor da direita
                    // (menor dos maiores)
                    Node *tmp = min(node->right);

                    // copia somente o valor para o nodo atual
                    node->data = tmp->data;

                    // deleta o sucessor
                    node->right = node->right->remove(tmp->data);
                }
            }

            if (node == NULL) return node;

            // atualizar altura do nodo atual
            node->height_ = std::max(height(node->left),
                                        height(node->right)) + 1;

            // pegar balanço para ver se precisa rodar
            int balance = get_balance(node);

            // caso esteja desbalanceado (4 casos)
            // esquerda-esquerda
            if (
                balance > 1 &&
                get_balance(node->left) >= 0
            ) {
                return simpleLeft(node);
            }

            // esquerda-direita
            if (
                balance > 1 &&
                get_balance(node->left) < 0
            ) {
                return doubleLeft(node);
            }

            // direita-direita
            if (
                balance < -1 &&
                get_balance(node->right) <= 0
            ) {
                return simpleRight(node);
            }

            // direita-esquerda
            if (
                balance < -1 &&
                get_balance(node->right) > 0
            ) {
                return doubleRight(node);
            }

            // retorna o nodo com/sem alteracoes
            return node;
        }

        // encontrar o menor valor da árvore da direita
        // (só ir para esquerda indefinidamente)
        Node *min(Node *node) {
            Node *now = node;
            if (node->left != NULL) return node->min(node->left);

            return now;
        }

        bool contains(const T &data_) const {
            if (data_ < data) {
                // está à esquerda
                return left != NULL ? left->contains(data_) : false;
            } else if (data_ > data) {
                // está à direita
                return right != NULL ? right->contains(data_) : false;
            } else if (data_ == data) {
                return true;
            } else {
                throw std::out_of_range("erro de elemento");
            }
        }

        void pre_order(ArrayList<T> &v) const {
            v.push_back(data);
            if (left != NULL) left->pre_order(v);
            if (right != NULL) right->pre_order(v);
        }

        void in_order(ArrayList<T> &v) const {
            if (left != NULL) left->in_order(v);
            v.push_back(data);
            if (right != NULL) right->in_order(v);
        }

        void post_order(ArrayList<T> &v) const {
            if (left != NULL) left->post_order(v);
            if (right != NULL) right->post_order(v);
            v.push_back(data);
        }

        void free() {
            if (right != NULL) right->free();
            if (left != NULL) left->free();

            if (this != NULL) delete this;
        }
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

// -----

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height(root);
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    // std::cout << "chamou o destrutor \n";
    // if (root != NULL) {
    //     if (root->right != NULL) root->right->free();
    //     if (root->left != NULL) root->left->free();
    // }
    // std::cout << "terminou o destrutor \n";
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0 ? true : false;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (root != NULL) {
        if (data < root->data) {
            // é menor -> esquerda da árvore
            return root->left != NULL ? root->left->contains(data) : false;

        } else if (data > root->data) {
            // é maior -> direita da árvore
            return root->right != NULL ? root->right->contains(data) : false;

        } else if (data == root->data) {
            // é a raiz da árvore
            return true;

        } else {
            throw std::out_of_range("erro de elemento");
        }
    } else {
        return false;
    }
}

template<typename T>
void structures::AVLTree<T>::insert(const T &data) {
    root = root->insert(root, data);

    // incrementa contador de elementos
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("arvore vazia! nao pode deletar elementos");
    } else {
        root = root->remove(data);

        // decrementa contador de elementos
        size_--;
    }
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> lista;

    if (root != NULL) {
        root->pre_order(lista);
    }

    return lista;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> lista;

    if (root != NULL) {
        root->in_order(lista);
    }

    return lista;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> lista;

    if (root != NULL) {
        root->post_order(lista);
    }

    return lista;
}
