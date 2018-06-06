#include <iostream>
#include "BinarySearchTree.hpp"

int main()
{
    // BinarySearchTree<int> test = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};

    // std::cout << test << std::endl;

    // std::cout << "removing node" << std::endl;
    // test.remove(14);
    // std::cout << "Done removing node" << std::endl;

    // std::cout << test << std::endl;

    BinarySearchTree<int> test = {1, 3, 5, 7, 9};
    BinarySearchTree<int> test2 = {8, 14, 9, 99, 12, 15, 18, 17, 16};

    test = std::move(test2);

    std::cout << test2 << std::endl;
    return 0;
}
