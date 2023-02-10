#include "tester.hpp"

int main() {

    std::cout << GREEN << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "Testing STACK . . ." << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << END << std::endl;

    testStack();
    testRealStack();

    std::cout << GREEN << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "Testing VECTOR . . ." << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << END << std::endl;    
    
    testVector();
    testRealVector();

    std::cout << GREEN << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "Testing MAP . . ." << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << END << std::endl;

    testMap();
    testRealMap();
    return (0);
}