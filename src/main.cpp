#include <array>
#include <iostream>
#include <vector>

#include "dsa/binary_search_tree.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &stream, const dsa::BinarySearchTree<T> &bst)
{
    bst.inorder([&](const T &key) { stream << key << ' '; });
    return stream;
}

int main()
{
    // create tree
    {
        dsa::BinarySearchTree<int> tree;
    }
    {
        dsa::BinarySearchTree<int> tree{4, 1, 2};
    }
    {
        std::vector<int> v = {6, 1, 3};
        dsa::BinarySearchTree<int> tree = v;
        dsa::BinarySearchTree<int> tree1(v);
    }
    {
        std::array<int, 4> arr = {7, 2, 3, 7};
        dsa::BinarySearchTree<int> tree = arr;
        dsa::BinarySearchTree<int> tree1(arr);
    }
    {
        int arr[] = {7, 2, 3, 7};
        dsa::BinarySearchTree<int> tree = {arr, sizeof(arr) / sizeof(int)}; //
        dsa::BinarySearchTree<int> tree1(arr, sizeof(arr) / sizeof(int));
    }

    // tree operations
    dsa::BinarySearchTree<int> tree = {13, 6, 15, 17, 20, 9, 4, 3, 7, 2, 18};
    tree.search(15);
    tree.insert(19);
    tree.remove(18);

    // traverse tree
    dsa::BinarySearchTree<int> tree;
    auto print = [](const int val) { std::cout << val << ' '; };
    tree.inorder(print);
    tree.preorder(print);
    tree.postorder(print);

    // printing tree
    std::cout << tree << std::endl;
}
