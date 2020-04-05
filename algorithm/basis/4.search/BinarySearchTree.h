//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/4
//

#ifndef ALGORITHM_BINARYSEARCHTREE_H
#define ALGORITHM_BINARYSEARCHTREE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Key, typename Value>
class BinarySearchTree {

private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        };
    };

    int count;
    Node *root;

    Node *insert(Node *node, Key key, Value value) {
        if (node == NULL) {
            count++;
            return new Node(key, value);
        }
        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        return node;
    }

    bool contain(Node *node, Key key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return contain(node->left, key);
        } else if (key > node->key) {
            return contain(node->right, key);
        }
    }

    Value *search(Node *node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key == node->key) {
            return &(node->value);
        } else if (key < node->key) {
            return search(node->left, key);
        } else if (key > node->key) {
            return search(node->right, key);
        }
    }

    void preOrder(Node *node) {
        if (node != nullptr) {
            cout << node->key << "|" << node->value << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void middleOrder(Node *node) {
        if (node != nullptr) {
            middleOrder(node->left);
            cout << node->key << "|" << node->value << endl;
            middleOrder(node->right);
        }
    }

    void postOrder(Node *node) {
        if (node != nullptr) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << "|" << node->value << endl;
        }
    }

    void destroy(Node *node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);

            delete node;
            count--;
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
        count = 0;
    }

    ~BinarySearchTree() {
        destroy(root);
    }

    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contain(Key key) {
        return contain(root, key);
    }

    Value *search(Key key) {
        return search(root, key);
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void preOrder() {
        preOrder(root);
    }

    void middleOrder() {
        middleOrder(root);
    }

    void postOrder() {
        postOrder(root);
    }

    void destroy() {
        destroy(root);
    }
};


#endif //ALGORITHM_BINARYSEARCHTREE_H
