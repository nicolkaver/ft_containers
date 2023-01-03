#include "containers/Vector.hpp"

int main() {
    ft::vector<int> v1(5, 3);

    std::cout << v1.at(1) << std::endl;
    return 0;
}