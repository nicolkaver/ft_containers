#include <vector>
#include <iostream>
#include <iterator>

int main() {
    std::vector<int> vec;
    vec.push_back(1); vec.push_back(1); vec.push_back(1); vec.push_back(1);
    vec.push_back(1);
    auto ite = vec.end();
    vec.insert(ite, 2);
    for (auto it = vec.begin(); it != vec.end(); it++)
        std::cout << *it << std::endl;
}