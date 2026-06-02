// Copyright 2021 NNTU-CS

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;

    while (!file.eof()) {
        int ch = file.get();
        if (ch == EOF) break;

        if (ch >= 0 && ch <= 127 &&
                std::isalpha(static_cast<unsigned char>(ch))) {
            word += static_cast<char>(
                std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<BSTNode<std::string>*> nodes;
    tree.inorder([&nodes](BSTNode<std::string>* node) {
        nodes.push_back(node);
    });

    std::sort(nodes.begin(), nodes.end(),
        [](const BSTNode<std::string>* a, const BSTNode<std::string>* b) {
            if (a->count != b->count) return a->count > b->count;
            return a->key < b->key;
        });

    for (const auto* node : nodes) {
        std::cout << node->key << " : " << node->count << "\n";
    }

    std::ofstream out("result/freq.txt");
    if (out) {
        for (const auto* node : nodes) {
            out << node->key << " : " << node->count << "\n";
        }
        out.close();
    } else {
        std::cerr << "Warning: could not write result/freq.txt\n";
    }
}
