#pragma once

#include <memory>
#include <ostream>
#include <type_traits>

namespace dsa {

    template <typename T>
    struct LinkedListNode {
    public:
        using NodeUniquePtr = std::unique_ptr<LinkedListNode>;
        using NodePtr = LinkedListNode *;

        T key;
        NodeUniquePtr next;
        NodePtr prev;

        template <typename Ref>
        LinkedListNode(Ref &&key, const NodePtr prev)
            : key{std::forward<Ref>(key)}, next{}, prev(prev) {}

    }; // struct LinkedListNode

    template <class List>
    class LinkedListConstIterator {
        friend List;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = typename List::value_type;
        using pointer = const value_type *;
        using reference = const value_type &;

        using NodeUniquePtr = typename List::NodeUniquePtr;

    protected:
        const NodeUniquePtr *curr_;

    public:
        LinkedListConstIterator(const NodeUniquePtr &node) : curr_(&node) {}

        reference operator*() const { return (*curr_)->key; }
        pointer operator->() const { return &*(*this); }

        LinkedListConstIterator &operator++()
        {
            curr_ = &(*curr_)->next;
            return *this;
        }

        LinkedListConstIterator operator++(int)
        {
            LinkedListConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const LinkedListConstIterator &other) const { return curr_ == other.curr_; }
        bool operator!=(const LinkedListConstIterator &other) const { return !(*this == other); }

    }; // class LinkedListConstIterator

    template <class List>
    class LinkedListIterator : public LinkedListConstIterator<List> {
    public:
        using value_type = typename List::value_type;
        using pointer = value_type *;
        using reference = value_type &;

        reference operator*() const { return (*this->curr_)->key; }
        pointer operator->() const { return &*(*this); }

        LinkedListIterator &operator++()
        {
            this->curr_ = &(*this->curr_)->next;
            return *this;
        }

        LinkedListIterator operator++(int)
        {
            LinkedListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

    }; // class LinkedListIterator

    template <typename T>
    class LinkedList {
    public:
        using value_type = T;

        using Node = LinkedListNode<value_type>;
        using NodeUniquePtr = typename Node::NodeUniquePtr;
        using NodePtr = typename Node::NodePtr;

        using const_iterator = LinkedListConstIterator<LinkedList>;
        using iterator = LinkedListIterator<LinkedList>;

    private:
        NodeUniquePtr head_;
        NodePtr tail_;

    public:
        // constructors

        template <typename... Args,
                  typename = std::enable_if_t<
                      std::conjunction_v<std::is_constructible<value_type, Args>...>>>
        LinkedList(Args &&...args) : head_{}, tail_{}
        {
            (insert(std::forward<Args>(args)), ...);
        }

        LinkedList(const LinkedList &other) : head_{}, tail_{}
        {
            for (const auto &el : other) {
                insert(el);
            }
        }

        LinkedList(LinkedList &&other)
            : head_(std::move(other.head_)), tail_(other.tail_)
        {
            other.tail_ = nullptr;
        }

        // operators

        LinkedList &operator=(const LinkedList &other)
        {
            if (this != &other) {
                clear();

                for (const auto &el : other) {
                    insert(el);
                }
            }
            return *this;
        }

        LinkedList &operator=(LinkedList &&other)
        {
            if (this != &other) {
                head_ = std::move(other.head_);
                tail_ = other.tail_;
                other.tail_ = nullptr;
            }
            return *this;
        }

        // iterators

        const_iterator begin() const { return {head_}; }
        const_iterator end() const { return {tail_ ? tail_->next : head_}; }

        iterator begin() { return {head_}; }
        iterator end() { return {tail_ ? tail_->next : head_}; }

        // linked list operations

        void clear()
        {
            head_.reset();
            tail_ = nullptr;
        }

        template <typename Ref>
        void insert(Ref &&key)
        {
            NodeUniquePtr &next = tail_ ? tail_->next : head_;

            next = std::make_unique<Node>(std::forward<Ref>(key), tail_);
            tail_ = next.get();
        }

        bool remove(const value_type &key)
        {
            for (auto it = begin(), end_ = end(); it != end_; ++it) {
                if (*it == key) {
                    auto &curr = *const_cast<NodeUniquePtr *>(it.curr_);

                    (curr->next
                         ? curr->next->prev // not tail
                         : tail_            // tail
                     ) = curr->prev;

                    curr = std::move(curr->next);
                    return true;
                }
            }
            return false;
        }

        // printing

        friend std::ostream &operator<<(std::ostream &os, const LinkedList &list)
        {
            for (const auto &el : list) {
                os << el << ' ';
            }
            return os;
        }

    }; // class LinkedList

} // namespace dsa
