#pragma once

#include <functional>
#include <initializer_list>
#include <memory>

namespace dsa {

    template <typename T>
    class BinarySearchTree {

    public:
        struct Node {
            T key;
            std::shared_ptr<Node> left, right;
            std::weak_ptr<Node> parent;
        };

        using NodePtr = std::shared_ptr<Node>;
        using TraversalCallback = std::function<void(const T &)>;

    private:
        NodePtr root;

    public:
        // constructors
        BinarySearchTree() = default;

        BinarySearchTree(const T *array, size_t size)
        {
            for (size_t i = 0; i < size; i++) {
                insert(array[i]);
            }
        }

        BinarySearchTree(const std::initializer_list<T> &list)
        {
            for (const auto &key : list) {
                insert(key);
            }
        }

        template <class Iter>
        BinarySearchTree(const Iter &iterable)
        {
            for (const auto &key : iterable) {
                insert(key);
            }
        }

        // tree traversal
        static void inorder(const NodePtr &node, const TraversalCallback &callback)
        {
            if (node) {
                inorder(node->left, callback);
                callback(node->key);
                inorder(node->right, callback);
            }
        }

        void inorder(const TraversalCallback &callback) const
        {
            inorder(root, callback);
        }

        static void preorder(const NodePtr &node, const TraversalCallback &callback)
        {
            if (node) {
                callback(node->key);
                preorder(node->left, callback);
                preorder(node->right, callback);
            }
        }

        void preorder(const TraversalCallback &callback) const
        {
            preorder(root, callback);
        }

        static void postorder(const NodePtr &node, const TraversalCallback &callback)
        {
            if (node) {
                postorder(node->left, callback);
                postorder(node->right, callback);
                callback(node->key);
            }
        }

        void postorder(const TraversalCallback &callback) const
        {
            postorder(root, callback);
        }

        // tree search
        static NodePtr search(const NodePtr &node, const T &key)
        {
            const NodePtr *nodePP = &node;
            while (*nodePP != nullptr && key != (**nodePP).key) {
                if (key < (**nodePP).key) {
                    nodePP = &(**nodePP).left;
                }
                else {
                    nodePP = &(**nodePP).right;
                }
            }
            return *nodePP;
        }

        NodePtr search(const T &key) const
        {
            return search(root, key);
        }

        // min max
        static NodePtr minimum(const NodePtr &node)
        {
            const NodePtr *nodePP = &node;
            while ((**nodePP).left != nullptr) {
                nodePP = &(**nodePP).left;
            }
            return *nodePP;
        }

        NodePtr minimum()
        {
            return minimum(root);
        }

        static NodePtr maximum(const NodePtr &node)
        {
            const NodePtr *nodePP = &node;
            while ((**nodePP).right != nullptr) {
                nodePP = &(**nodePP).right;
            }
            return *nodePP;
        }

        NodePtr maximum()
        {
            return maximum(root);
        }

        // successor
        static NodePtr successor(const NodePtr &node);

        // insert remove
        void insert(const T &key);
        void transplant(const NodePtr &a, const NodePtr &b);
        NodePtr remove(const T &key);
    };

}
