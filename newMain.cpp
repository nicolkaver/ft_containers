#include "containers/map.hpp"
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
    ft::map<int, std::string> mp;
    mp[1] = "one";
    mp[2] = "two";
    mp[3] = "three";
    mp[4] = "four";
    mp[5] = "five";
    mp[6] = "six";

    auto it = mp.find(3);
    std::cout << it->first << "." << it->second;
    return 0;
}