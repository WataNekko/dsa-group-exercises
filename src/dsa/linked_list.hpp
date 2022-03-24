#pragma once

#include <memory>

namespace dsa {

    template <typename T>
    class LinkedList {
    public:
        struct Node {
            T key;
            std::shared_ptr<Node> next;
            std::weak_ptr<Node> prev;
        };

    private:
        Node head;
    };

} // namespace dsa
