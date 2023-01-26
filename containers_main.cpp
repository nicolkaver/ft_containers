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

void testStack(void) {
    struct timeval diff, start, end;
    ft::stack<int> st;
    gettimeofday(&start, NULL);

    st.push(21);
    st.push(22);
    st.push(24);
    st.push(25);
    int num = 26;
    st.push(num);
    ft::stack<int> st2;
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

    if (mp.count(2) == 1)
        std::cout << "LOL\n";

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
    //mp2 = mp;
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

int main() {

    // testStack();
    // testRealStack();
    // testRealMap();
    testMap();
    return (0);
}