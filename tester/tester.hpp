#ifndef TESTER_HPP
# define TESTER_HPP

# include <iostream>
# include <string>
# include <deque>
# include "../containers/map.hpp"
# include "../containers/stack.hpp"
# include "../containers/vector.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/IteratorTraits.hpp"
# include "../utils/Node.hpp"
# include "../utils/Pair.hpp"
# include "../utils/randomAccessIterator.hpp"
# include "../utils/RBTree.hpp"
# include "../utils/RBTreeIterator.hpp"
# include "../utils/RBTreeReverseIterator.hpp"
# include "../utils/ReverseIterator.hpp"
# include "../utils/TypeTraits.hpp"

# include <ctime>
# include <sys/time.h>

# include <stack>
# include <vector>
# include <map>

# define GREEN "\033[1;32m"
# define BOLD "\033[1;3m"
# define END "\033[0m"

//STACK
void testRealStack(void);
void testStack(void);

//VECTOR

void testRealVector(void);
void testVector(void);

//MAP
void testRealMap(void);
void testMap(void);

int main(void);


#endif