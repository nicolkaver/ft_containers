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
#define BOLD "\033[1;3m"
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
    std::cout << BOLD << "ft::stack: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << END << std::endl;
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
    std::cout << BOLD << "std::stack: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << END << std::endl;
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
    if (vec2.size() == 4)
        std::cout << "Tested size" << std::endl;
    while (!vec.empty())
        vec.pop_back();
    std::cout << "Tested empty" << std::endl << "Tested pop_back" << std::endl;
    
    std::vector<int> vec3;
    size_t store = 5;
    vec3.reserve(store);
    if (vec3.capacity() == store)
        std::cout << "Tested reserve" << std::endl << "Tested capacity" << std::endl;

    vec2.insert(vec2.end(), 3, 6);
    vec2.erase(vec2.end());
    if (vec2.size() == 6)
        std::cout << "Tested insert" << std::endl << "Tested erase" << std::endl;

    vec2.resize(9, 9);
    ite = vec2.end() - 1;
    if (vec2.size() == 9 && *ite == 9)
        std::cout << "Tested resize" << std::endl;

    for (int i = 1; i < 6; i++)
        vec.push_back(i);

    vec.swap(vec2);
    if (vec.size() == 9 && vec2.size() == 5)
        std::cout << "Tested swap" << std::endl;

    vec2.clear();
    if (!vec2.size())
        std::cout << "Tested clear" << std::endl;

    int test = 1000000;
    for (int i = 0; i < test; i++)
        vec2.push_back(i);
    for (int i = 0; i < test; i++)
        vec2.pop_back();

    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
}

void testMap(void) {
    ft::map<int, int> mp;
    struct timeval diff, start, end;
    gettimeofday(&start, NULL);

    mp[1] = 1;
    mp[2] = 2;
    mp[3] = 3;
    std::cout << "Tested constructor" << std::endl;
    
    ft::map<int, int> mp2 = mp;
    ft::map<int, int>::iterator it = mp2.begin();
    // int test = 1000000;
    // for (int i = 0; i < test; i++)
    //     mp[i] = i;
    // for (int i = 0; i < test; i++)
    //     mp.erase(i);

    
    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
    std::cout << "ft::map: " << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void simpleTest(void) {
    ft::vector<int> vec;
    std::cout << vec.max_size() << std::endl;
}

int main() {

    std::cout << GREEN << "Testing stack . . ." << END << std::endl;
    //testStack();
    // testRealStack();
    std::cout << GREEN << "Testing vector . . ." << END << std::endl;
    // testVector();
    // testRealVector();
    std::cout << GREEN << "Testing map . . ." << END << std::endl;
    // testMap();
    // testRealMap();
    simpleTest();
    return (0);
}