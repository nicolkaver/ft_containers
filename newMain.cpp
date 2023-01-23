#include "containers/Map.hpp"
#include "utils/algorithm.hpp"
#include "utils/IteratorTraits.hpp"
#include "utils/Node.hpp"
#include "utils/Pair.hpp"
#include "utils/RBTree.hpp"
#include "utils/RBTreeIterator.hpp"
#include "utils/RBTreeReverseIterator.hpp"
#include "utils/TypeTraits.hpp"

#include <iostream>

int main() {
    ft::map<int, int> mp;
    // ft::map<int, int> mp2;
    mp[1] = 1;
    mp[3] = 3;
    
    ft::map<int, int> mp2;
    mp2 = mp;
    std::cout << mp2[1] << std::endl;
    
    // try {
    //     std::cout << mp.at(2) << std::endl;
    // } catch (std::exception & e) {
    //     std::cerr << e.what() << std::endl;
    // }
    return 0;
}