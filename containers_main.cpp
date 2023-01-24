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
    mp[1] = 1;
    mp.erase(1);
}

int main() {

    // testStack();
    // testRealStack();
    testMap();
    return (0);
}