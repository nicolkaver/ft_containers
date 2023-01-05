#include "containers/Vector.hpp"
#include <iostream>
#include "utils/randomAccessIterator.hpp"
//#include <iterator>

int main() {
    ft::vector<int> v1;
    ft::vector<int> v2;
    ft::RandomAccessIterator<int> it;
    ft::RandomAccessIterator<int> ite;

    v1.push_back(2);
    v2.push_back(3);
    v1.swap(v2);
    it = v1.begin();
    std::cout << *it << std::endl;
    return 0;
}