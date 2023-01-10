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

template<typename T, typename Compare, typename Allocator>
class RBTree {
public:
    typedef Node<T> Node;
    typedef T value_type;
    typedef typename value_type::first_type key_type;

    typedef ft::RBTreeIterator<T, Node> iterator;
    typedef ft::RBTreeIterator<const T, const Node> const_iterator;
    typedef ft::RBTreeReverseIterator<T, Node> reverse_iterator;
    typedef ft::RBTreeReverseIterator<const T, const Node> const_reverse_iterator;

    typedef Allocator allocator_type;
    typedef typename allocator_type::template rebind<Node>::other node_allocator; //custom memory allocator; will allocate Node
    typedef Compare key_compare;
    
    RBtree(): _root(NULL), _superRoot(NULL), _dummyRoot(NULL), _comp(key_compare()), _allocator(allocator_type()),
                _nodeAllocator(node_allocator()) {
        _superRoot = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(_superRoot, Node(value_type()));
        _dummyRoot = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(_dummyRoot, Node(value_type()));
    }

    RBTree(RBTree const & src):_root(NULL), _superRoot(NULL), _dummyRoot(NULL) { *this = src; }
    
    ~RBTree() { //clear}

    RBTree & operator=(RBTree const & rhs) { //continue}


// RELATIVE NODES
private:
    Node* getSibling(Node* node) {
        if (node == NULL && node->parent == NULL)
            return (NULL);
        if (node == node->parent->left)
            return (node->parent->right);
        if (node == node->parent->right)
            return (node->parent->left);
    }

    Node* getGrandparent(Node* node) {
        if (node == NULL && node->parent == NULL && node->parent->parent == NULL)
            return (NULL);
        else
            return (node->parent->parent);
    }

    Node* getUncle(Node* node) {
        if (node == NULL && node->parent == NULL && node->parent->parent == NULL)
            return (NULL);
        else
            return (getSibling(node->parent));
    }

// ROTATIONS

private:
    void rotateLeft(Node* node) {
        if (node == NULL)
            return ;
        Node* ptr_right = node->right;
        node->right = ptr_right->left;
        if (node->right != NULL)
            node->right->parent = node;
        ptr_right->parent = node->parent;
        if (node->parent == NULL)
            _root = ptr_right;
        else if (node == node->parent->left)
            node->parent->left = ptr_right;
        else
            node->parent->right = ptr_right;
        ptr_right->left = node;
        node->parent = ptr_right;
    }

    void rotateRight(Node* node) {
        if (node == NULL)
            return ;
        Node* ptr_left = node->left;
        node->left = ptr_left->right;
        if (node->left != NULL)
            ptr_left->right->parent = node;
        ptr_left->parent = node->parent;
        if (node->parent == NULL)
            _root = ptr_left;
        else if (node == node->parent->right)
            node->parent->right = ptr_left;
        else
            node->parent->left = ptr_left;
        ptr_left_right = node;
        node->parent = ptr_left;
    }

// REPLACE

    void replace(Node* n1, Node* n2) {
        if (n1 == NULL)
            _root = n2;
        else if (n1 == n1->parent->left)
            n1->parent->left = n2;
        else
            n1->parent->right = n2;
        if (n2 != NULL)
            n2->parent = n1->parent;
    }

// ITERATORS


// CLEAR

public:
    void clear() {

    }

    void clear2(Node* node) {
        if (node == NULL || node == _dummyRoot)
            return ;
    }
        

private:
    Node* _root;
    Node* _superRoot;
    Node* _dummyRoot;
    key_compare _comp;
    allocator_type _allocator;
    node_allocator _nodeAllocator;
};

} //namespace ft

#endif