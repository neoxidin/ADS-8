// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;

    const char* filename = "src/war_peace.txt";

    std::cout << "Building BST from: " << filename << " ...\n";
    makeTree(tree, filename);

    std::cout << "Tree depth (height): " << tree.depth() << "\n";

    const std::string testWord = "war";
    int count = tree.search(testWord);
    if (count)
        std::cout << "Word \"" << testWord
                  << "\" found, count = " << count << "\n";
    else
        std::cout << "Word \"" << testWord << "\" not found.\n";

    std::cout << "\n--- Frequency table (descending) ---\n";
    printFreq(tree);

    return 0;
}
