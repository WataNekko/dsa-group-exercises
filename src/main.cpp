#include <iostream>

#include "dsa/linked_list.hpp"

int main()
{
    dsa::LinkedList<int> list = {1, 2, 3, 4, 69};
    std::cout << list << '\n';
    std::cout << list.search(69) << '\n';
    list.insert(6);
    std::cout << list << '\n';
    list.remove(2);
    std::cout << list << '\n';
}