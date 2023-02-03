#ifndef RED_BLACK_TREE_ITERATOR
# define RED_BLACK_TREE_ITERATOR

# include <iostream>
# include "Node.hpp"
# include "Pair.hpp"
# include "TypeTraits.hpp"
# include "RBTree.hpp"

namespace ft {
template<typename T, typename U>
class RBTreeIterator {
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    typedef U Node;

    RBTreeIterator(): _ptr(NULL) {}
    RBTreeIterator(Node* ptr): _ptr(ptr) {}
    RBTreeIterator(RBTreeIterator const & src): _ptr(src._ptr) {}
    ~RBTreeIterator() {}

    RBTreeIterator & operator=(RBTreeIterator const & rhs) {
        if (this != &rhs)
            this->_ptr = rhs._ptr;
        return (*this);
    }

    template <typename T1, typename U1>
    RBTreeIterator(const RBTreeIterator<T1, U1>& other) : _ptr(other.getPtr()){};

    Node* getPtr(void) const { return (_ptr); }

    friend bool operator==(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return (lhs._ptr == rhs._ptr);
    }
    friend bool operator!=(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return (lhs._ptr != rhs._ptr);
    }

    friend bool operator>(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return lhs._ptr > rhs._ptr;
    }

    friend bool operator>=(const RBTreeIterator& lhs,
                         const RBTreeIterator& rhs) {
        return lhs._ptr >= rhs._ptr;
    }

    friend bool operator<(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return lhs._ptr < rhs._ptr;
    }

    friend bool operator<=(const RBTreeIterator& lhs,
                        const RBTreeIterator& rhs) {
        return lhs._ptr <= rhs._ptr;
    }

    reference operator*() { return (_ptr->data); }

    pointer operator->() { return (&(_ptr->data)); }

    reference operator*() const { return *_ptr; }
    pointer operator->() const { return _ptr; }

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

    // Node* getSuccessor(Node* node) {
    //     if (node == NULL)
    //         return (NULL);
    //     if (node->right)
    //         return (getMinValue(node->right));
    //     Node* parent = node->parent;
    //     while (parent && node == parent->right) {
    //         node = parent;
    //         parent = parent->parent;
    //     }
    //     return (parent);
    // }

    // Node* getPredecessor(Node* node) {
    //     if (node == NULL)
    //         return (NULL);
    //     if (node->left)
    //         return (getMaxValue(node->left));
    //     Node* parent = node->parent;
    //     while (parent && node == parent->left) {
    //         node = parent;
    //         parent = parent->parent;
    //     }
    //     return (parent);
    // }

        Node* getSuccessor(Node* node) {
        if (node == NULL)
           return (NULL);
        if (node->right != NULL) {
            return (getMinValue(node->right));
        }
        else {
        Node* parent = node->parent;
        // while (node->data > parent->data)
        //         parent = parent->parent;
        while (parent && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return (parent);
        }
    }

    Node* getPredecessor(Node* node) {
        //if (node == NULL)
        //    return (NULL);
        Node* parent = node->parent;
        if (node->left)
            return (getMaxValue(node->left));
        // while (node->data < parent->data)
        //     parent = parent->parent; 
        while (parent && node == parent->left) {
            node = parent;
            parent = parent->parent;       
        }
        return (parent);
    }


private:
    Node* _ptr;
};


} // namespace ft


#endif