#ifndef R_B_TREE_HPP
# define R_B_TREE_HPP

# include <iostream>
# include "Node.hpp"
# include "RBTreeIterator.hpp"

namespace ft {
template<typename T, typename U>
class RBTreeIterator;

template<typename T, typename U>
class RBTreeReverseIterator;

class RBTree {
public:


    typedef ft::RBTreeIterator<T, Node> iterator;
    typedef ft::RBTreeIterator<const T, const Node> const_iterator;
    typedef ft::RBTreeReverseIterator<T, Node> reverse_iterator;
    typedef ft::RBTreeReverseIterator<const T, const Node> const_reverse_iterator;

    
};

} //namespace ft

#endif