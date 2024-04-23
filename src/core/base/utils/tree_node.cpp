#include "src/core/utils/tree_node.h"


namespace Utility {
    namespace NodeUtils {

        template<typename T>
        BinaryNode<T>::~BinaryNode() {
            delete left;
            delete right;
        }

        template<typename T>
        TreeNode<T>::~TreeNode() {
            for (auto child : children) {
                delete child;
            }
        }

        template<typename T>
        void TreeNode<T>::addChild(TreeNode<T>* child) {
            children.push_back(child);
        }

        template<typename T>
        void TreeNode<T>::traverse(const std::function<void(T)>& visit) {
            visit(value);
            for (auto child : children) {
                child->traverse(visit);
            }
        }
    }
}

// Explicit template instantiation for required types
template class Utility::NodeUtils::BinaryNode<int>;
template class Utility::NodeUtils::TreeNode<int>;