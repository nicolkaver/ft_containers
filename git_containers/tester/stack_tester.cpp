#include "tester.hpp"

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
    std::cout << "Tested size" << std::endl << "Tested empty" << std::endl; 
    std::cout << "Tested pop" << std::endl;
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

    std::cout << BOLD << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "FT::STACK: " << diff.tv_sec << ".";
    std::cout << diff.tv_usec << " seconds" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << END << std::endl;
}

void testRealStack(void) {
    struct timeval diff, start, end;
    std::stack<int> st;
    std::cout << "Constructor worked" << std::endl;
    gettimeofday(&start, NULL);

    st.push(21);
    st.push(22);
    st.push(24);
    st.push(25);
    int num = 26;
    st.push(num);
    std::cout << "Tested push" << std::endl;
    std::stack<int> st2;
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

    std::cout << BOLD << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "STD::STACK: " << diff.tv_sec << ".";
    std::cout << diff.tv_usec << " seconds" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << END << std::endl;
}