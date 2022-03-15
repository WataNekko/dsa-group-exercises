#include <iostream>

#include "dsa/binary_search_tree.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &stream, const dsa::BinarySearchTree<T> &bst)
{
    bst.inorder([&](const T &key) { stream << key << ' '; });
    return stream;
}

int main()
{
    dsa::BinarySearchTree<int> tree = {13, 6, 15, 17, 20, 9, 4, 3, 7, 2, 18};
    std::cout << tree << "(binary search tree)\n"
              << std::endl;

    tree.insert(18);
    std::cout << tree << "(inserted 18)" << std::endl;
    tree.insert(11);
    std::cout << tree << "(inserted 11)" << std::endl;
    tree.insert(25);
    std::cout << tree << "(inserted 25)\n"
              << std::endl;

    tree.remove(6);
    std::cout << tree << "(removed 6)" << std::endl;
    tree.remove(13);
    std::cout << tree << "(removed 13)" << std::endl;
    tree.remove(18);
    std::cout << tree << "(removed 18)\n"
              << std::endl;

    std::cout << (tree.search(7) ? "Found " : "Cannot find ") << 7 << std::endl;
    std::cout << (tree.search(19) ? "Found " : "Cannot find ") << 19 << std::endl;
}
