#pragma once

#include <initializer_list>
#include <memory>
#include <ostream>

namespace dsa {

    template <typename T>
    class LinkedList {
    public:
        struct Node {
            T key;
            std::shared_ptr<Node> next;
            std::weak_ptr<Node> prev;

            Node(const T &key, std::shared_ptr<Node> next)
                : key(key), next(std::move(next)), prev{} {}
        };

        LinkedList(std::initializer_list<T> list)
        {
            for (auto it = std::rbegin(list),
                      end = std::rend(list);
                 it != end;
                 ++it) {
                insert(*it);
            }
        }

        void insert(const T &key)
        {
            head_ = std::make_shared<Node>(key, std::move(head_));
            if (head_->next) {
                head_->next->prev = head_;
            }
        }

        std::shared_ptr<Node> remove(const T &key)
        {
            auto node = search(key);
            if (node) {
                node->next->prev = node->prev;
                node->prev.lock()->next = std::move(node->next);
                node->prev.reset();
            }
            return node;
        }

        std::shared_ptr<Node> search(const T &key) const
        {
            const std::shared_ptr<Node> *curr = &head_;
            while (*curr != nullptr && (*curr)->key != key) {
                curr = &(*curr)->next;
            }
            return *curr;
        }

        friend std::ostream &operator<<(std::ostream &os, const LinkedList &list)
        {
            const std::shared_ptr<Node> *curr = &list.head_;
            while (*curr != nullptr) {
                os << (*curr)->key << ' ';
                curr = &(*curr)->next;
            }
            return os;
        }

    private:
        std::shared_ptr<Node> head_;
    };

} // namespace dsa
