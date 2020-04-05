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
#include <queue>

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
            this->left = this->right = nullptr;
        };

        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = this->right = nullptr;
        }
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

    Node *findMaxNode(Node *node) {
        if (node->left == nullptr) {
            return node;
        }
        return findMaxNode(node->left);
    }

    Node *findMinNode(Node *node) {
        if (node->right == nullptr) {
            return node;
        }
        return findMinNode(node->right);
    }

    Node *removeMinNode(Node *node) {
        if (node->left == nullptr) {
            Node *nodeLeft = node->left;
            delete node;
            count--;
            return nodeLeft;
        }
        node->left = removeMinNode(node->left);
        return node;
    }

    Node *removeMaxNode(Node *node) {
        if (node->right == nullptr) {
            Node *nodeRight = node->right;
            delete node;
            count--;
            return nodeRight;
        }
        node->right = removeMinNode(node->right);
        return node;
    }

    Node *remove(Node *node, Key key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        }

        if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        }
        // key == node->key
        if (node->left == nullptr) {
            Node *rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }
        if (node->right == nullptr) {
            Node *leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }

        Node *resNode = new Node(findMinNode(node->right));
        count++;

        resNode->right = removeMinNode(node->right);
        resNode->left = node->left;

        delete node;
        count--;
        return resNode;
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

    void levelOrder() {
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            cout << node->key << "|" << node->value << endl;
            if (node->left) {
                q.push(node->left);
            }

            if (node->right) {
                q.push(node->right);
            }
        }
    }

    void findMaxNode() {
        findMaxNode(root);
    }

    void findMinNode() {
        findMinNode(root);
    }

    void removeMinNode() {
        removeMinNode(root);
    }

    void removeMaxNode() {
        removeMaxNode(root);
    }

    void remove(Key key) {
        root = remove(root, key);
    }
};


#endif //ALGORITHM_BINARYSEARCHTREE_H
