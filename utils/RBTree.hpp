#ifndef R_B_TREE_HPP
# define R_B_TREE_HPP

# include <iostream>
# include "Node.hpp"
# include "RBTreeIterator.hpp"
# include "RBTreeReverseIterator.hpp"
# include "TypeTraits.hpp"
# include "IteratorTraits.hpp"
# include "Pair.hpp"

# define RED 1
# define BLACK 0

// help: https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp

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
    typedef typename value_type::first_type key_value;

    typedef ft::RBTreeIterator<T, Node> iterator;
    typedef ft::RBTreeIterator<const T, const Node> const_iterator;
    typedef ft::RBTreeReverseIterator<T, Node> reverse_iterator;
    typedef ft::RBTreeReverseIterator<const T, const Node> const_reverse_iterator;

    typedef Allocator allocator_type;
    typedef typename allocator_type::template rebind<Node>::other node_allocator; //custom memory allocator; will allocate Node
    typedef Compare key_compare;
    
    RBTree(): _root(NULL), _endNode(NULL), _bottomNode(NULL), _comp(key_compare()), _allocator(allocator_type()),
                _nodeAllocator(node_allocator()) {
        _endNode = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(_endNode, Node(value_type()));
        _bottomNode = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(_bottomNode, Node(value_type()));
    }

    RBTree(RBTree const & src): _root(NULL), _endNode(NULL), _bottomNode(NULL) { *this = src; }
    
    ~RBTree() {
        clear();
        clearRoots();
    }

    RBTree & operator=(RBTree const & rhs) {
        if (this != &rhs) {
            clear();
            clearRoots();

            _allocator = rhs._allocator;
            _nodeAllocator = rhs._nodeAllocator;
            _comp = rhs._comp;
            _endNode = _nodeAllocator.allocate(1);
            _nodeAllocator.construct(_endNode, Node(value_type()));
            _bottomNode = _nodeAllocator.allocate(1);
            _nodeAllocator.construct(_bottomNode, Node(value_type()));
            _root = clone(rhs._root, NULL, rhs._bottomNode);
            if (_root) {
                _root->parent = _endNode;
                _endNode->left = _root;
                Node *minNode = getMin(_root);
                _bottomNode->parent = minNode;
                minNode->left = _bottomNode;
            }
        }
        return (*this);
    }


// RELATIVE NODES
private:
    Node* getSibling(Node* node) {
        if (node == NULL || node->parent == NULL)
            return (NULL);
        if (node == node->parent->left)
            return (node->parent->right);
        else
            return (node->parent->left);
    }

    Node* getGrandparent(Node* node) {
        if (node != NULL && node->parent != NULL && node->parent->parent != NULL)
            return (node->parent->parent);
        else
            return (NULL);
    }

    Node* getUncle(Node* node) {
        if (node != NULL && node->parent != NULL && node->parent->parent != NULL)
            return (getSibling(node->parent));
        else
            return (NULL);
    }

// ROTATIONS

private:

    // void rotateLeft(Node* node) {
    //     if (node == NULL)
    //         return ;
    //     Node* tmp = node->right;
    //     replace(node, tmp);
    //     if (node && tmp)
    //         node->right = tmp->left;
    //     if (tmp && tmp->left != NULL)
    //         tmp->left->parent = node;
    //     if (tmp)
    //         tmp->left = node;
    //     node->parent = tmp;
    // }

    // void rotateRight(Node* node) {
    //     if (node == NULL)
    //         return ;
    //     Node* tmp = node->left;
    //     replace(node, tmp);
    //     if (node && tmp)
    //         node->left = tmp->right;
    //     if (tmp && tmp->right != NULL)
    //         tmp->right->parent = node;
    //     if (tmp)
    //         tmp->right = node;
    //     node->parent = tmp;
    // }

    void rotateLeft(Node* node) {
        if (node == NULL)
            return ;
        Node* ptr_right = node->right;
        node->right = ptr_right->left;
        if (node->right != NULL)
            ptr_right->left->parent = node;
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
        ptr_left->right = node;
        node->parent = ptr_left;
    }

// REPLACE

public:
    void replace(Node* n1, Node* n2) {
        if (n1->parent == NULL)
            _root = n2;
        else if (n1 == n1->parent->left)
            n1->parent->left = n2;
        else
            n1->parent->right = n2;
        if (n2 != NULL)
            n2->parent = n1->parent;
    }

// ITERATORS

public: 
iterator lower_bound(key_value const & key) {
    Node* tmp = _root;
    Node* ret = _endNode;
    while (tmp && tmp != _bottomNode) {
        if (key <= tmp->data.first) {
            ret = tmp;
            tmp = tmp->left;
        }
        else
            tmp = tmp->right;
    }
    return (iterator(ret));
}

const_iterator lower_bound(key_value const & key) const {
    Node* tmp = _root;
    Node* ret = _endNode;
    while (tmp && tmp != _bottomNode) {
        if (key <= tmp->data.first) {
            ret = tmp;
            tmp = tmp->left;
        }
        else
            tmp = tmp->right;
    }
    return (const_iterator(ret));
}

iterator upper_bound(key_value const & key) { // A VERIFIER !!!
    Node* tmp = _root;
    Node* ret = _endNode;
    while (tmp) {
        if (key < tmp->data.first) {
            ret = tmp;
            tmp = tmp->left;
        }
        else
            tmp = tmp->right;
    }
    return (iterator(ret));
}

const_iterator upper_bound(key_value const & key) const { // A VERIFIER !!!
    Node* tmp = _root;
    Node* ret = _endNode;
    while (tmp) {
        if (key < tmp->data.first) {
            ret = tmp;
            tmp = tmp->left;
        }
        else
            tmp = tmp->right;
    }
    return (const_iterator(ret));
}

iterator begin() { return (iterator(getBegin())); }

const_iterator begin() const { return (const_iterator(getBegin())); }

iterator end() { return (iterator(_endNode)); }

const_iterator end() const { return (const_iterator(_endNode)); }

reverse_iterator rbegin() { //continue
    if (_root == NULL)
        return (reverse_iterator(_bottomNode));
    else {
        reverse_iterator it = _endNode;
        it++;
        return (it);
    }
}

const_reverse_iterator rbegin() const { //continue
    if (_root == NULL)
        return (cosnt_reverse_iterator(_bottomNode));
    else {
        const_reverse_iterator it = _endNode;
        it++;
        return (it);
    }
}

reverse_iterator rend() { return (reverse_iterator(_bottomNode)); }

//const_reverse_iterator rend() { return (const_reverse_iterator(_bottomNode())); }

// CLEAR

public:
    void clear() {
        clear2(_root);
        _root = NULL;
    }

private:
    void clear2(Node* node) {
        if (node == NULL || node == _bottomNode || node == _endNode)
            return ;
        else {
            clear2(node->left);
            clear2(node->right);
            _nodeAllocator.destroy(node);
            _nodeAllocator.deallocate(node, 1);
        }
    }

    void    clearRoots() {
        if (_endNode) {
            _nodeAllocator.destroy(_endNode);
            _nodeAllocator.deallocate(_endNode, 1);
        }
        if (_bottomNode) {
            _nodeAllocator.destroy(_bottomNode);
            _nodeAllocator.deallocate(_bottomNode, 1);
        }
    }

// SEARCH FUNCTIONS
public :
    iterator search(key_value const & key) {
        Node* ret = searchHelper(_root, key);
        if (ret)
            return (iterator(ret));
        else
            return (end());
    }

    iterator search(key_value const & key) const {
        Node* ret = searchHelper(_root, key);
        if (ret)
            return (iterator(ret));
        else
            return (end());
    }

    Node* searchHelper(Node* root, key_value const & key) {
        if (root == NULL || root == _bottomNode)
            return (NULL);
        else {
        if (root->data.first == key)
            return (root);
        else if (key < root->data.first) //
            return (searchHelper(root->left, key));
        else
            return (searchHelper(root->right, key));
        }
    }

    Node* searchHelper(Node* root, key_value const & key) const {
        if (root == NULL || root == _bottomNode)
            return (NULL);
        if (root->data.first == key)
            return (root);
        if (root->data.first && key < root->data.first) //
            return (searchHelper(root->left, key));
        else
            return (searchHelper(root->right, key));
    }

// INSERT FUNCTIONS

public:
    iterator insertNode(value_type const & data) {
        if (_root != NULL) {
            _root->parent = NULL;
            _bottomNode->parent->left = NULL;
            _bottomNode->parent = NULL;
        }
        _endNode->left = NULL;
        Node* newNode = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(newNode, Node(data));
        //we verify whether the root exists
        // if not, we make the new node the root
        if (_root == NULL)
            _root = newNode;
        else {
            Node* tmp = _root;
            while (1) {
                if (data.first == tmp->data.first) {
                    tmp->data.second = data.second;
                    return (tmp);
                }
                else if (data.first < tmp->data.first) {
                    if (tmp->left == NULL) {
                        tmp->left = newNode;
                        break;
                    }
                    else
                        tmp = tmp->left;
                }
                else {
                    if (tmp->right == NULL) {
                        tmp->right = newNode;
                        break;
                    }
                    else
                        tmp = tmp->right;
                }
            }
            newNode->parent = tmp;
        }
        insert_case1(newNode);
        _root->parent = _endNode;
        _endNode->left = _root;
        Node *smallestNode = getMin(_root);
        smallestNode->left = _bottomNode;
        _bottomNode->parent = smallestNode;
        return (search(data.first));
    }

// the 5 cases from https://www.happycoders.eu/algorithms/red-black-tree-java/
// https://iq.opengenus.org/red-black-tree-insertion/
private:
    void insert_case1(Node* node) {
        if (node->parent == NULL)
            node->color = BLACK;
        else
            insert_case2(node);
    }

    void insert_case2(Node* node) {
        if (node->parent->color == BLACK)
            return ;
        else
            insert_case3(node);
    }

    void insert_case3(Node* node) {
        if (getUncle(node) && getUncle(node)->color == RED) {
            node->parent->color = BLACK;
            getUncle(node)->color = BLACK;
            getGrandparent(node)->color = RED;
            insert_case1(getGrandparent(node));
        }
        else
            insert_case4(node);
    }

    void insert_case4(Node* node) {
        if (node == node->parent->right
            && (getGrandparent(node) && node->parent == getGrandparent(node)->left)) {
                rotateLeft(node->parent);
                node = node->left;
        }
        else if (node == node->parent->left
                    && (getGrandparent(node) && node->parent == getGrandparent(node)->right)) {
            rotateRight(node->parent);
            node = node->right;
        }
        insert_case5(node);
    }

    void insert_case5(Node* node) {
        node->parent->color = BLACK;
        getGrandparent(node)->color = RED;
        if (node == node->parent->left
            && (getGrandparent(node) && node->parent == getGrandparent(node)->left)) {
            rotateRight(getGrandparent(node));
        }
        else {
            rotateLeft(getGrandparent(node));
        }
    }

// CLONE

Node* clone(Node* curr, Node* parent, Node* bottom) {
    if (curr != NULL && curr != bottom) {
        Node* node = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(node, Node(curr->data));
        node->parent = parent;
        node->left = clone(node->left, node, bottom);
        node->right = clone(node->right, node, bottom);
        return (node);
    }
    else
        return (NULL);
}

// DELETIONS
//https://codingdiksha.com/cpp-program-implement-red-black-tree/

public:
    void deleteNode(key_value const & key) {
        if (_root) {
            _root->parent = NULL;
            _endNode->left = NULL;
            _bottomNode->parent->left = NULL;
            _bottomNode->parent = NULL;
        }
        Node* child;
        Node* node = searchHelper(_root, key);
        if (node == NULL)
            return ;
        if (node->left != NULL && node->right != NULL) {
            Node* pred = getMax(node->left);
            bool isLeft = false;
            if (node->parent && node->parent->left == node)
                isLeft = true;
        //we create temporary copy of the deleted node that we 
        //will later connect to its predecessor
            Node* tmpParent = node->parent;
            Node* tmpRight = node->right;
            Node* tmpLeft = node->left;
            int tmpColor = node->color;
            _nodeAllocator.destroy(node);
            _nodeAllocator.deallocate(node, 1);
            node = _nodeAllocator.allocate(1);
            _nodeAllocator.construct(node, Node(pred->data));
        //now we connect the copy to the predecessor
            if (tmpParent) {
                node->parent = tmpParent;
            if (isLeft)
                tmpParent->left = node;
            else
                tmpParent->right = node;
            }
            if (tmpLeft) {
                tmpLeft->parent = node;
                node->left = tmpLeft;
            }
            if (tmpRight) {
                tmpRight->parent = node;
                node->right = tmpRight;
            }
            node->color = tmpColor;
            node = pred;
        }
        child = node->right == NULL ? node->left : node->right;
        if (node->color == BLACK) {
            if (child != NULL)
                node->color = child->color;
            else
                node->color = BLACK;
            delete_case1(node);
        }
        replace(node, child);
        _nodeAllocator.destroy(node);
        _nodeAllocator.deallocate(node, 1);
        if (_root) {
            _root->parent = _endNode;
            _endNode->left = _root;
            Node *minNode = getMin(_root);
            _bottomNode->parent = minNode;
            minNode->left = _bottomNode;
        }
    }

private:
    void delete_case1(Node* node) {
        if (node->parent == NULL)
            return ;
        else
            delete_case2(node);
    }

    void delete_case2(Node* node) {
        if (getSibling(node) && getSibling(node)->color == RED) {
            node->parent->color = RED;
            getSibling(node)->color = BLACK;
            if (node == node->parent->left)
                rotateLeft(node->parent);
            else
                rotateRight(node->parent);
        }
        delete_case3(node);
    }

    void delete_case3(Node* node) {
        if (node->parent->color == BLACK && getSibling(node)
            && getSibling(node)->color == BLACK
            && (getSibling(node)->left == NULL || getSibling(node)->left->color == BLACK)
            && (getSibling(node)->right == NULL || getSibling(node)->right->color == BLACK)) {
            getSibling(node)->color = RED;
            delete_case1(node->parent);
        }
        else
            delete_case4(node);
    }

    void delete_case4(Node* node) {
        if (node->parent->color == RED && getSibling(node)
            && getSibling(node)->color == BLACK
            && (getSibling(node)->left == NULL || getSibling(node)->left->color == BLACK) 
            && (getSibling(node)->right == NULL ||getSibling(node)->right->color == BLACK)) {
            getSibling(node)->color = RED;
            node->parent->color = BLACK;
        }
        else
            delete_case5(node);
    }

    void delete_case5(Node* node) {
        if (node == node->parent->left && getSibling(node)
            && getSibling(node)->color == BLACK && getSibling(node)->left 
            && getSibling(node)->left->color == RED
            && (getSibling(node)->right == NULL || getSibling(node)->right->color == BLACK)) {
                getSibling(node)->color = RED;
                getSibling(node)->left->color = BLACK;
                rotateRight(getSibling(node));
        }
        else if (node == node->parent->right && getSibling(node)
                    && getSibling(node)->color == BLACK
                    && getSibling(node)->right && getSibling(node)->right->color == RED
                    && (getSibling(node)->left == NULL
                        || getSibling(node)->left->color == BLACK)) {
            getSibling(node)->color = RED;
            getSibling(node)->right->color = BLACK;
            rotateLeft(getSibling(node));
        }
        delete_case6(node);
    }

    void delete_case6(Node* node) {
        if(getSibling(node))
            getSibling(node)->color = node->parent->color;
        node->parent->color = BLACK;
        if (node == node->parent->left) {
            if (getSibling(node) && getSibling(node)->right->color == RED)
                getSibling(node)->right->color = BLACK;
            rotateLeft(node->parent);
        }
        else {
            if (getSibling(node) && getSibling(node)->left->color == RED)
                getSibling(node)->left->color = BLACK;
            rotateRight(node->parent);
        }
    }

// MIN AND MAX

Node* getMin(Node* node) {
    while (node && node->left && node->left != _bottomNode)
        node = node->left;
    return (node);
}

Node* getMax(Node* node) {
    while (node && node->right)
        node = node->right;
    return (node);
}

Node* getRoot() { return (_root); }

Node* getBegin() {
    if (_root == NULL)
        return (_endNode);
    Node* node = _root;
    while (node && node->left != NULL && node->left != _bottomNode)
        node = node->left;
    return (node);
}

Node* getBegin() const {
    if (_root == NULL)
        return (_endNode);
    Node* node = _root;
    while (node && node->left != NULL && node->left != _bottomNode)
        node = node->left;
    return (node);
}

private:
    Node* _root;
    Node* _endNode;
    Node* _bottomNode;
    key_compare _comp;
    allocator_type _allocator;
    node_allocator _nodeAllocator;
};

} //namespace ft

#endif