#pragma once

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include "src/core/utils/utility.h"


namespace Utility {
    namespace NodeUtils {

        template <typename T>
        class BinaryNode {
        public:
            T value;  // The data held by the BinaryNode
            BinaryNode<T>* left;  // Pointer to the left child
            BinaryNode<T>* right; // Pointer to the right child

            // Constructor initializes node with a value and optional children
            BinaryNode(T val, BinaryNode<T>* leftChild = nullptr, BinaryNode<T>* rightChild = nullptr)
                : value(val), left(leftChild), right(rightChild) {}

            // Destructor to clean up resources
            ~BinaryNode();
        };

        template <typename T>
        class TreeNode {
        public:
            T value;
            std::vector<TreeNode<T>*> children;  // Vector to hold pointers to child nodes

            // Constructor to initialize node with a value
            TreeNode(const T& val) : value(val) {}

            // Destructor to clean up resources
            ~TreeNode();

            // Add a child node to this node
            void addChild(TreeNode<T>* child);

            // Function to traverse the tree depth-first and apply a function to each node's value
            void traverse(const std::function<void(T)>& visit);
        };
    }
}
#endif