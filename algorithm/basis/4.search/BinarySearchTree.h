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

public:
    BinarySearchTree() {
        root = nullptr;
        count = 0;
    }

    ~BinarySearchTree() {

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
};


#endif //ALGORITHM_BINARYSEARCHTREE_H
