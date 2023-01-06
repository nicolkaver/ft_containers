#include "containers/Vector.hpp"
#include <iostream>
#include "utils/randomAccessIterator.hpp"
#include <vector>
//#include <iterator>

using vecIt = std::vector<int>::iterator;

int main() {
    ft::vector<int> v1;
    std::vector<int> v2;
    ft::RandomAccessIterator<int> it;
    ft::RandomAccessIterator<int> ite;
    vecIt it2;
    vecIt ite2;

    v1.push_back(2); v1.push_back(2); v1.push_back(2); v1.push_back(2); v1.push_back(2); // 5 x 2
    v2.push_back(2); v2.push_back(2); v2.push_back(2); v2.push_back(2); v2.push_back(2);

    it = v1.begin();
    ite = v1.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << "*************" << std::endl;
    it2 = v2.begin();
    ite2 = v2.end();
    for (; it2 != ite2; it2++)
        std::cout << *it2 << std::endl;
    std::cout << std::endl << "ASSIGN:" << std::endl;
    v1.assign(5, 9);
    v2.assign(5, 9);
    it = v1.begin();
    ite = v1.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << "*************" << std::endl;
    it2 = v2.begin();
    ite2 = v2.end();
    for (; it2 != ite2; it2++)
        std::cout << *it2 << std::endl;
    std::cout << v1.size() << " " << v2.size() << std::endl;
    std::cout << v1.capacity() << " " << v2.capacity() << std::endl;
    return 0;
}