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

            Node(const T &key, const std::shared_ptr<Node> &parent)
                : key(key), parent(parent) {}

            Node(const std::shared_ptr<Node> &other)
                : key(other->key),
                  left(clone(other->left)),
                  right(clone(other->right)) {}

            static std::shared_ptr<Node> clone(const std::shared_ptr<Node> &src)
            {
                if (!src) {
                    return nullptr;
                }

                auto node = std::make_shared<Node>(src);
                if (node) {
                    if (node->left) {
                        node->left->parent = node;
                    }
                    if (node->right) {
                        node->right->parent = node;
                    }
                }

                return node;
            }
        };

        using NodePtr = std::shared_ptr<Node>;
        using TraversalCallback = std::function<void(const T &)>;

    private:
        NodePtr root_;

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

        BinarySearchTree(const BinarySearchTree &other)
            : root_(Node::clone(other.root_)) {}

        BinarySearchTree &operator=(const BinarySearchTree &other)
        {
            if (this != &other) {
                root_ = Node::clone(other.root_);
            }
            return *this;
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
            inorder(root_, callback);
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
            preorder(root_, callback);
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
            postorder(root_, callback);
        }

        // tree search
    private:
        static NodePtr &search_(const NodePtr &node, const T &key)
        {
            const NodePtr *nodePP = &node;
            while (*nodePP != nullptr && key != (*nodePP)->key) {
                if (key < (*nodePP)->key) {
                    nodePP = &(*nodePP)->left;
                }
                else {
                    nodePP = &(*nodePP)->right;
                }
            }
            return const_cast<NodePtr &>(*nodePP);
        }

        NodePtr &search_(const T &key) const
        {
            return search_(root_, key);
        }

    public:
        static NodePtr search(const NodePtr &node, const T &key)
        {
            return search_(node, key);
        }

        NodePtr search(const T &key) const
        {
            return search_(root_, key);
        }

        // min max
    private:
        static NodePtr &minimum_(const NodePtr &node)
        {
            const NodePtr *nodePP = &node;
            while ((*nodePP)->left != nullptr) {
                nodePP = &(*nodePP)->left;
            }
            return const_cast<NodePtr &>(*nodePP);
        }

    public:
        static NodePtr minimum(const NodePtr &node)
        {
            return minimum_(node);
        }

        NodePtr minimum() const
        {
            return minimum_(root_);
        }

        static NodePtr maximum(const NodePtr &node)
        {
            const NodePtr *nodePP = &node;
            while ((*nodePP)->right != nullptr) {
                nodePP = &(*nodePP)->right;
            }
            return *nodePP;
        }

        NodePtr maximum() const
        {
            return maximum(root_);
        }

        // successor

        static NodePtr successor(const NodePtr &node)
        {
            if (node->right) {
                return minimum(node->right);
            }

            NodePtr child = node;
            NodePtr parent = child->parent.lock();
            while (parent != nullptr && child == parent->right) {
                child = parent;
                parent = parent->parent.lock();
            }
            return parent;
        }

        // insert remove

        void insert(const T &key)
        {
            NodePtr *child = &root_;
            const NodePtr *parent = child;

            while (*child != nullptr) {
                parent = child;

                if (key < (*child)->key) {
                    child = &(*child)->left;
                }
                else {
                    child = &(*child)->right;
                }
            }

            *child = std::make_shared<Node>(key, *parent);
        }

    private:
        static void transplant(NodePtr &dest, const NodePtr &src)
        {
            if (src != nullptr) {
                // setting src's parent
                if (dest != nullptr) {
                    src->parent = dest->parent;
                }
                else {
                    src->parent.reset();
                }
            }
            if (dest != nullptr) {
                // resetting parent at old dest object
                dest->parent.reset();
            }

            dest = src;
        }

    public:
        /**
         * Remove the element from the tree. Return false if the element is not found, otherwise true.
         */
        bool remove(const T &key)
        {
            NodePtr &nodeRef = search_(key);

            if (!nodeRef) {
                // not found
                return false;
            }

            if (!nodeRef->left) {
                NodePtr removed = nodeRef;
                transplant(nodeRef, nodeRef->right);
                removed->right.reset();
            }
            else if (!nodeRef->right) {
                NodePtr removed = nodeRef;
                transplant(nodeRef, nodeRef->left);
                removed->left.reset();
            }
            else {
                NodePtr &successorRef = minimum_(nodeRef->right);
                NodePtr successor = successorRef;

                if (successorRef->parent.lock() != nodeRef) {
                    transplant(successorRef, successorRef->right);
                    successor->right = nodeRef->right;
                    successor->right->parent = successor;
                }

                NodePtr removed = nodeRef;
                transplant(nodeRef, successor);
                successor->left = removed->left;
                successor->left->parent = successor;

                removed->left.reset();
                removed->right.reset();
            }

            return true;
        }

    }; // class BinarySearchTree

} // namespace dsa
