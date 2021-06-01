
#include "array_list.h"

namespace structures {
template<typename T>
  //! avl tree
class AVLTree {
public:
    //! avl_tree node
    struct Node {
        //! data of the node
        T key;
        //! left node
        Node* left;
        //! right node
        Node* right;
        //! height of the node
        int height;
        
        Node(T data) {
            key = data;
            left = NULL;
            right = NULL;
            height = 1;
        }
    };

    //! function for creating a new node with data
    Node* newNode(T data) {
        auto* node = new Node(data);
        return node;
    }
    //! Auxiliary function to get the max between 2 numbers
    int max(int a, int b) {
        return ((a > b) ? a : b);
    }
    //! Returns the height of the node
    int avl_height(Node* node) {
        if (node == NULL) {
            return 0;
        } else {
            return node->height;
        }
    }
    //! Performs a simple right rotation
    Node* simpleRight(Node* node) {
        auto* x = node->left;
        auto* T2 = x->right;

        x->right = node;
        node->left = T2;

        x->height    = max(avl_height(x->left), avl_height(x->right))+1;
        node->height = max(avl_height(node->left), avl_height(node->right))+1;

        return x;
    }
    //! Performs a simple left rotation
    Node* simpleLeft(Node* node) {
        auto* y = node->right;
        auto* T2 = y->left;

        y->left = node;
        node->right = T2;

        node->height = max(avl_height(node->left), avl_height(node->right))+1;
        y->height    = max(avl_height(y->left), avl_height(y->right))+1;

        return y;
    }

    Node* doubleRight(Node* node) {
        node->left = simpleLeft(node->left);
        return simpleRight(node);
    }
    Node* doubleLeft(Node* node) {
        node->right = simpleRight(node->right);
        return simpleLeft(node);
    }

    //! gets the balance of the node
    int balance(Node* node) {
        if (node == NULL)
            return 0;
        return avl_height(node->left) - avl_height(node->right);
    }
    //! inserts nodes into the tree
    Node* insert(Node* node, T data) {
        // if (node == NULL) {
        //     return newNode(data);
        // } else if (data < node->key) {
        //     node->left = insert(node->left, data);
        //     if (avl_height(node->left) - avl_height(node->right) == 2) {
                
        //         if (data < node->left->key) {
        //             node = simpleRight(node);
        //         } else {
        //             node = doubleRight(node);
        //         }
        //     }
        
        // } else if (data > node->key) {
        //     node->right = insert(node->right, data);
            
        //     if (data > node->right->key) {
        //         node = simpleLeft(node);
        //     } else {
        //         node = doubleLeft(node);
        //     }
        // }
        
        // node->height = max(avl_height(node->left), avl_height(node->right)+1);
        
        if (node == NULL)
            return newNode(data);
        if (data < node->key)
            node->left = insert(node->left, data);
        else if (data > node->key)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + max(avl_height(node->left),
                               avl_height(node->right));

        auto balance_ = balance(node);

        if (balance_ > 1 && data < node->left->key)
            return simpleRight(node);

        if (balance_ < -1 && data > node->right->key)
            return simpleLeft(node);

        if (balance_ > 1 && data > node->left->key) {
            node->left = simpleLeft(node->left);
            return simpleRight(node);
        }

        if (balance_ < -1 && data < node->right->key) {
            node->right = simpleRight(node->right);
            return simpleLeft(node);
        }

        return node;
    }
    //! returns the node with minimum key
    Node* min_node(struct Node* node) {
        auto* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }
    //! removes a node from the tree
    Node* deleteNode(Node* node, T key) {
        if (node == NULL)
            return node;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);

        } else {
            if ((node->left == NULL) || (node->right == NULL)) {
                auto* temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                auto temp = min_node(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (node == NULL)
            return node;

        node->height = 1+ max(avl_height(node->left), avl_height(node->right));

        auto balance_ = balance(node);

        if (balance_ > 1 && balance(node->left) >= 0)
            return simpleRight(node);

        if (balance_ > 1 && balance(node->left) < 0) {
            node->left = simpleLeft(node->left);
            return simpleRight(node);
        }

        if (balance_ < -1 && balance(node->right) <= 0)
            return simpleLeft(node);

        if (balance_ < -1 && balance(node) > 0) {
            node->right = simpleRight(node->right);
            return simpleLeft(node);
        }

        return node;
    }
    //! checks the existance of an item in the tree
    bool contains(Node* node, T data) const {
        if (node->key == data) {
            return true;
        } else if (node->key > data) {
            if (node->left != NULL) {
                return contains(node->left, data);
            } else {
                return false;
            }
        } else if (node->right != NULL) {
            return contains(node->right, data);
        } else {
            return false;
        }
    }
    //! root of the tree
    Node* root;
    //! ammount of nodes of the tree
    int size_;

    AVLTree() {
        size_ = 0;
        root = NULL;
    }

    ~AVLTree() {
        clear(root);
    }
    //! clears the tree
    void clear(Node* tree) {
        // if (tree != NULL) {
        //     clear(tree->right);
        //     clear(tree->left);
        //     delete tree;
        // }
        // tree = nullptr;
    }
    //! inserts elements
    void insert(T data) {
        root = insert(root, data);
        size_++;
    }
    //! removes elements
    void remove(T data) {
        root = deleteNode(root, data);
        size_--;
    }
    //! checks existance of elements
    bool contains(const T& data) const {
        return contains(root, data);
    }
    //! checks if empty
    bool empty() const {
        return (size_ == 0)? true : false;
    }
    //! returns size
    int size() const {
        return size_;
    }
    //! fills an array in preorder
    void preOrder(ArrayList<T>& ar, Node* pre) {
        if (pre != NULL) {
            ar.push_back(pre->key);
            preOrder(ar, pre->left);
            preOrder(ar, pre->right);
        }
    }
    //! fills an array in preorder
    ArrayList<T> pre_order() {
        ArrayList<T> ar{static_cast<std::size_t>(size_)};
        preOrder(ar, root);
        return ar;
    }
    //! fills an array in inorder
    void inOrder(ArrayList<T>& ar, Node* pre) {
        if (pre != NULL) {
            preOrder(ar, pre->left);
            ar.push_back(pre->key);
            preOrder(ar, pre->right);
        }
    }
    //! fills an array in inorder
    ArrayList<T> in_order() {
        ArrayList<T> ar{static_cast<std::size_t>(size_)};
        inOrder(ar, root);
        return ar;
    }
    //! fills an array in postorder
    void postOrder(ArrayList<T>& ar, Node* pre) {
        if (pre != NULL) {
            preOrder(ar, pre->left);
            preOrder(ar, pre->right);
            ar.push_back(pre->key);
        }
    }
    //! fills an array in postorder
    ArrayList<T> post_order() {
        ArrayList<T> ar{static_cast<std::size_t>(size_)};
        postOrder(ar, root);
        return ar;
    }
};
}  // namespace structures