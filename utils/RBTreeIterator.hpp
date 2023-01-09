#ifndef RED_BLACK_TREE_ITERATOR
# define RED_BLACK_TREE_ITERATOR

# include <iostream>
# include "Node.hpp"


namespace ft {
template<typename T, typename U>
class RBTreeIterator {
public:
    typedef typename bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    typedef U Node;

    RBTreeIterator(): _ptr(NULL) {}
    RBTreeIterator(ptr): _ptr(ptr) {}
    RBTreeIterator(RBTreeIterator const & src) { *this = src; }
    ~RBTreeIterator() {}

    RBTreeIterator & operator=(RBTreeIterator const & rhs) {
        this->_ptr = rhs._ptr;
        return (*this);
    }

    friend bool operator==(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return lhs._ptr == rhs._ptr;
    }
    friend bool operator!=(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return lhs._ptr != rhs._ptr;
    }

    reference operator*() { return *_ptr; }
    pointer operator->() { return _ptr; }

    const_reference operator*() const { return *_ptr; }
    const_pointer operator->() const { return _ptr; }

    RBTreeIterator operator++() {
        _ptr = getSuccessor(_ptr);
        return *this;
    }

    RBTreeIterator operator++(int) {
        RBTreeIterator tmp = *this;
        operator++();
        return tmp;
    }

    RBTreeIterator operator--() {
        _ptr = getPredecessor(_ptr);
        return *this;
    }

    RBTreeIterator operator--(int) {
        RBTreeIterator tmp = *this;
        operator--();
        return tmp;
    }

    Node* getMinValue(Node* node) {
        if (node && node->left)
            node = node->left;
        return (node);
    }

    Node* getMaxValue(Node* node) {
        if (node && node->right)
            node = node->right;
        return (node);
    }

    Node* getSuccessor(Node* node) {
        if (node == NULL)
            return (NULL);
        Node* parent = node->parent;
        if (node->right)
            return (getMinValue(node->right));
        while (node->data > parent->data)
                parent = parent->parent;
        return (parent);
    }

    Node* getPredecessor(Node* node) {
        if (node == NULL)
            return (NULL);
        Node* parent = node->parent;
        if (node->left)
            return (getMaxValue(node->left));
        while (node->data < parent->data)
            parent = parent->parent;        
        return (parent);
    }

private:
    Node* _ptr;
};


} // namespace ft


#endif