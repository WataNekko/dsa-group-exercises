#pragma once

#include <memory>

namespace dsa {

    template <typename T>
    class BinarySearchTree {

    public:
        struct Node {
            T key;
            std::weak_ptr<Node> parent;
            std::shared_ptr<Node> left, right;
        };

    private:
        std::shared_ptr<Node> root;
    };

}
