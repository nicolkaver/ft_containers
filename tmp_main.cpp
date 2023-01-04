#include "containers/Vector.hpp"
#include <iostream>
#include "utils/randomAccessIterator.hpp"
//#include <iterator>

int main() {
    ft::vector<int> v1;
    ft::RandomAccessIterator<int> it;
    ft::RandomAccessIterator<int> ite;
    v1.push_back(2);
    // std::cout << *it << std::endl;
    v1.push_back(2);     
    v1.push_back(2);     
    v1.push_back(2);     v1.push_back(2);     v1.push_back(2);
    ite = v1.end();
    // std::cout << *ite << std::endl;
    it = v1.begin();
    // for (; it != ite; it++) {
    //     std::cout << *it << std::endl;
    // }
    it = v1.begin();
    v1.insert(it, 1, 3);
    std::cout << "new" << v1.at(1) << std::endl;
    // it = v1.begin();
    // for (; it != ite; it++) {
    //     std::cout << *it << std::endl;
    // }
    // std::cout << v1.at(1) << std::endl;
    return 0;
}