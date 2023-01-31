#include <iostream>
#include <string>
#include <deque>
#include "containers/map.hpp"
#include "containers/stack.hpp"
#include "containers/vector.hpp"
#include "utils/algorithm.hpp"
#include "utils/IteratorTraits.hpp"
#include "utils/Node.hpp"
#include "utils/Pair.hpp"
#include "utils/randomAccessIterator.hpp"
#include "utils/RBTree.hpp"
#include "utils/RBTreeIterator.hpp"
#include "utils/RBTreeReverseIterator.hpp"
#include "utils/ReverseIterator.hpp"
#include "utils/TypeTraits.hpp"

#include <ctime>
#include <sys/time.h>

#include <stack>
#include <vector>
#include <map>

#define GREEN "\033[1;32m"
#define END "\033[0m"

void testStack(void) {
    struct timeval diff, start, end;
    ft::stack<int> st;
    std::cout << "Constructor worked" << std::endl;
    gettimeofday(&start, NULL);

    st.push(21);
    st.push(22);
    st.push(24);
    st.push(25);
    int num = 26;
    st.push(num);
    std::cout << "Tested push" << std::endl;
    ft::stack<int> st2;
    st2 = st;
    std::cout << "Tested operator=" << std::endl;
    if (st.size() == st2.size()) {
        while (!st.empty())
            st.pop();
    }
    std::cout << "Tested size" << std::endl << "Tested empty" << std::endl << "Tested pop" << std::endl;
    st.push(1);
    if (st2 > st) {
        while (!st2.empty())
            st2.pop();
    }
    if (st.top() == 1)
        st.pop();

    int test = 1000000;
    for (int i = 0; i < test; i++)
        st.push(i);
    for (int i = 0; i < test; i++)
        st.pop();

    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
    std::cout << "ft::stack: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void testRealStack(void) {
    struct timeval diff, start, end;
    std::stack<int> st;
    gettimeofday(&start, NULL);

    st.push(21);
    st.push(22);
    st.push(24);
    st.push(25);
    int num = 26;
    st.push(num);
    std::stack<int> st2;
    st2 = st;
    if (st.size() == st2.size()) {
        while (!st.empty())
            st.pop();
    }
    st.push(1);
    if (st2 > st) {
        while (!st2.empty())
            st2.pop();
    }

    int test = 1000000;
    for (int i = 0; i < test; i++)
        st.push(i);
    for (int i = 0; i < test; i++)
        st.pop();

    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
    std::cout << "std::stack: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void testMap(void) {
    ft::map<int, int> mp;
    struct timeval diff, start, end;
    gettimeofday(&start, NULL);

    mp[1] = 1;
    mp[2] = 2;
    mp[3] = 3;
    mp.insert(ft::pair<int, int>(4, 4));

    ft::map<int, int>::iterator it;
    it = mp.begin();
    for (; it != mp.end(); it++)
        ;

    mp.erase(1);
    mp.erase(2);
    
    ft::map<int, int> mp2;
    mp2 = mp;
    if (mp.size() == mp2.size()) {
        mp.erase(3);
        mp2.erase(3);
    }

    int test = 1000000;
    for (int i = 0; i < test; i++)
        mp[i] = i;
    for (int i = 0; i < test; i++)
        mp.erase(i);
    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
    std::cout << "ft::map: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void testRealMap(void) {
    std::map<int, int> mp;
    struct timeval diff, start, end;
    gettimeofday(&start, NULL);

    mp[1] = 1;
    mp[2] = 2;
    mp.erase(2);
    mp.erase(1);
    
    mp[1] = 1;
    std::map<int, int> mp2 = mp;
    // mp2 = mp;
    if (mp.size() == mp2.size()) {
        mp.erase(1);
        mp2.erase(1);
    }


    int test = 1000000;
    for (int i = 0; i < test; i++)
        mp[i] = i;
    for (int i = 0; i < test; i++)
        mp.erase(i);
    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
    std::cout << "std::map: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void testVector(void) {
    ft::vector<int> vec;
    std::cout << "Constructor worked" << std::endl;
    struct timeval diff, start, end;
    gettimeofday(&start, NULL);

    vec.push_back(1);
    vec.assign(1, 1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << "Tested assign" << std::endl << "Tested push_back" << std::endl;
    if (vec.at(1) == vec[1] == vec.front() == vec.data()[0])
        vec.push_back(4);
    std::cout << "Tested at" << std::endl << "Tested operator[]" << std::endl;
    std::cout << "Tested front" << std::endl << "Tested data" << std::endl;
    if (vec.back() == 4)
        vec.push_back(5);
    std::cout << "Tested back" << std::endl;

    ft::vector<int>::iterator it = vec.begin();
    ft::vector<int>::iterator ite = vec.end();
    std::cout << "Tested begin" << std::endl << "Tested end" << std::endl;
    ft::vector<int> vec2;
    vec2.assign(it, ite);
    ft::vector<int>::reverse_iterator it1 = vec2.rbegin();
    ft::vector<int>::reverse_iterator it2 = vec2.rend();
    for (; it1 < it2; it1++)
        ;
    std::cout << "Tested rbegin" << std::endl << "Tested rend" << std::endl;
    if (vec2.empty())
        std::cout << "Tested empty" << std::endl;

    vec2.erase(vec2.begin());
    it = vec2.begin();
    ite = vec2.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;

    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
}

// void simpleTest(void) {
//     std::cout << "FT:\n";//testVector();
//     ft::vector<int> vec1;
//     ft::vector<int> vec2;
//     vec1.push_back(1);
//     vec2.push_back(2);
//     if (vec1 <= vec2)
//         std::cout << "LOL\n";
//     else
//         std::cout << "LALA\n";
    
//     std::cout << "STD:\n";
//     std::vector<int> vec3;
//     std::vector<int> vec4;
//     vec3.push_back(1);
//     vec4.push_back(2);
//     if (vec3 <= vec4)
//         std::cout << "LOL\n";
//     else
//         std::cout << "LALA\n";

// }

int main() {

    std::cout << GREEN << "Testing stack . . ." << END << std::endl;
    //testStack();
    // testRealStack();
    std::cout << GREEN << "Testing vector . . ." << END << std::endl;
    testVector();
    // testRealMap();
    //testMap();
    //simpleTest();
    return (0);
}