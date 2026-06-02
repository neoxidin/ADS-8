// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>

template <typename T>
struct BSTNode {
    T key;
    int count;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(const T& k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
 public:
    BST() : root_(nullptr) {}
    ~BST() { clear(root_); }

    void insert(const T& key) {
        root_ = insert(root_, key);
    }

    int search(const T& value) const {
        BSTNode<T>* node = search(root_, value);
        return node ? node->count : 0;
    }

    int depth() const {
        return depth(root_);
    }

    template <typename Visitor>
    void inorder(Visitor visit) const {
        inorder(root_, visit);
    }

    bool empty() const { return root_ == nullptr; }

 private:
    BSTNode<T>* root_;

    BSTNode<T>* insert(BSTNode<T>* node, const T& key) {
        if (!node) return new BSTNode<T>(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            node->count++;
        return node;
    }

    BSTNode<T>* search(BSTNode<T>* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->key) return node;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }

    int depth(BSTNode<T>* node) const {
        if (!node) return -1;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    template <typename Visitor>
    void inorder(BSTNode<T>* node, Visitor& visit) const {
        if (!node) return;
        inorder(node->left, visit);
        visit(node);
        inorder(node->right, visit);
    }

    void clear(BSTNode<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

#endif  // INCLUDE_BST_H_
