#include "containers/Vector.hpp"
#include <iostream>
#include "utils/randomAccessIterator.hpp"
#include "utils/RBTree.hpp"
#include "utils/RBTreeIterator.hpp"
#include "utils/RBTreeReverseIterator.hpp"

#include "containers/Map.hpp"

#include <map>

int main() {
    ft::map<int, int> mp;
    mp[1] = 1;
    mp[2] = 2;

    ft::map<int, int>::iterator it = mp.begin();
    ft::map<int, int>::iterator ite = mp.end();
    
    for (auto x : mp)
        std::cout << x.first << "->" << x.second << std::endl;
}