#ifndef RBTREE_REVERSE_ITERATOR
# define RBTREE_REVERSE_ITERATOR

# include <iostream>

namespace ft {
template<typename T, typename U>
class RBTreeReverseIterator {
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    typedef U Node;

    RBTreeReverseIterator() : _ptr(NULL){};
    RBTreeReverseIterator(Node* ptr) : _ptr(ptr) {};
    RBTreeReverseIterator(RBTreeReverseIterator const & src): _ptr(src._ptr) {}
    ~RBTreeReverseIterator() {}

    RBTreeReverseIterator & operator=(RBTreeReverseIterator const & rhs) {
        if (this != &rhs)
            _ptr = rhs._ptr;
        return (*this);
    }

    friend bool operator==(const RBTreeReverseIterator& lhs,
                            const RBTreeReverseIterator& rhs) {
    return (lhs._ptr == rhs._ptr);
    }

    friend bool operator!=(const RBTreeReverseIterator& lhs,
                            const RBTreeReverseIterator& rhs) {
        return (lhs._ptr != rhs._ptr);
    }

    reference operator*() { return (_ptr->data); }

    pointer operator->() { return (&(_ptr->data)); }

    RBTreeReverseIterator operator++() {
        _ptr = getPredecessor(_ptr);
        return *this;
    }

    RBTreeReverseIterator operator++(int) {
        RBTreeReverseIterator tmp = *this;
        operator++();
        return tmp;
    }

    RBTreeReverseIterator operator--() {
        _ptr = getSuccessor(_ptr);
        return *this;
    }

    RBTreeReverseIterator operator--(int) {
        RBTreeReverseIterator tmp = *this;
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