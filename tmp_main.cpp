#include "containers/Vector.hpp"
#include <iostream>
#include "utils/randomAccessIterator.hpp"
//#include <iterator>

int main() {
    ft::vector<int> v1;
    ft::RandomAccessIterator<int> it;
    ft::RandomAccessIterator<int> ite;
    v1.push_back(2);
    it = v1.begin();
    // std::cout << *it << std::endl;
    v1.push_back(2);     
    v1.push_back(2);     
    v1.push_back(2);     v1.push_back(2);     v1.push_back(2);
    ite = v1.end();
    // std::cout << *ite << std::endl;
    for (; it + 1 != ite; it++)
        std::cout << *it << std::endl;
    //v1.insert(it, 1, 3);
    //std::cout << v1.at(1) << std::endl;
    return 0;
}