#ifndef R_B_TREE_HPP
# define R_B_TREE_HPP

# include <iostream>
# include "Node.hpp"
# include "RBTreeIterator.hpp"

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
        clear2(_root);
        _root = NULL;
    }

private:
    void clear2(Node* node) {
        if (node == NULL || node == _dummyRoot)
            return ;
        else {
            clear2(node->right);
            clear2(node->left);
            _nodeAllocator.destroy(node);
            _nodeAllocator.deallocate(node, 1);
        }
    }

    void    clearRoots() {
        if (_superRoot) {
            _nodeAllocator.destroy(_superRoot);
            _nodeAllocator.deallocate(_superRoot, 1);
        }
        if (_dummyRoot)
            _nodeAllocator.destroy(_dummyRoot);
            _nodeAllocator.destroy(_dummyRoot, 1);
    }

// SEARCH FUNCTIONS
public :
    iterator search(key_type & const key) {
        Node* ret = searchHelper(_root, key);
        if (ret)
            return (iterator(ret));
        else
            return (end());
    }

    iterator search(key_type const & key) const {
        Node* ret = searchHelper(_root, key);
        if (ret)
            return (iterator(ret));
        else
            return (end());
    }

    Node* searchHelper(Node* root, key_type const & key) {
        if (root = NULL || root == _dummyRoot)
            return (NULL);
        if (root->data.first == key)
            return (root);
        if (key < root.data)
            return (searchHelper(root->left, key));
        else
            return (searchHelper(root->right, key));
    }

    Node* searchHelper(Node* root, key_type const & key) const {
        if (root = NULL || root == _dummyRoot)
            return (NULL);
        if (root->data.first == key)
            return (root);
        if (key < root.data)
            return (searchHelper(root->left, key));
        else
            return (searchHelper(root->right, key));
    }

// INSERT FUNCTIONS

public:
    iterator insert(value_type const & data) {
        if (_root != NULL) {
            _root->parent = NULL;
            _dummyRoot->parent->left = NULL;
            _dummyRoot->parent = NULL;
        }
        _superRoot->left = NULL;
        Node* newNode = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(newNode, Node(data));
        //we verify whether the root exists
        // if not, we make the new node the root
        if (_root == NULL)
            _root = newNode;
        else {
            Node* tmp = this->_root;
            if (data.first == tmp->data.first)
                tmp->data.second = data.second;
            else if (data < tmp->data) {
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
            newNode->parent = tmp;
        }
        insert_case1(newNode);
        _root->parent = _superRoot;
        _superRoot->left = _root;
        Node *smallestNode = getMinimum(_root);
        smallestNode->left = _dummyRoot;
        _dummyRoot->parent = smallestNode;
        return search(data.first);
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
        if (node && node == node->parent->right
            && node->parent == getGrandparent(node)->left) {
                rotateLeft(node->parent);
                node = node->left;
        }
        else if (node == node->parent->left
                    && node->parent == getGrandparent(node)->right)
            rotateRight(node->parent);
            node = node->right;
        }
        insert_case5(node);
    }

    void insert_case5(Node* node) {
        node->parent->color = BLACK;
        getGrandparent(node)->color = RED;
        if (node == node->parent->left
            && node->parent == getGrandparent(node)->left)
            rotateRight(getGrandparent(node));
        else
            rotateLeft(getGrandparent(node));
    }

// CLONE

// DELETIONS
//https://codingdiksha.com/cpp-program-implement-red-black-tree/

public:
    void delete(key_type const & key) {
        if (_root) {
            _root->parent = NULL;
            _superRoot->left = NULL;
            _dummyRoot->parent->left = NULL;
            _dummyRoot->parent = NULL;
        }
        Node* child;
        Node* node = searchHelper(_root, key);
        if (node == NULL)
            return ;
        if (node->left != NULL && node->righ != NULL) {
            Node* pred = maxNode(node->left);
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
        _nodeAllocator.allocate(1);
        _nodeAllocator.construct(node, Node(pred->data));
        //now we connect the copy to the predecessor
        if (tmp->parent) {
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
            node->color = child->color;
            delete_case1(node);
        }
        replace_node(node, child);
        _nodeAllocator.destroy(node);
        _nodeAllocator.deallocate(node, 1);
        if (_root) {
            _root->parent = _superRoot;
            _superRoot->left = _root;
            Node *minNode = getMinimum(_root);
            _dummyRoot->parent = minNode;
            minNode->left = _dummyRoot;
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
            && (getSibling(node)->right == NULL || getSibling(node)->right->color == BLACK) {
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
            && (getSibling(node->right == NULL ||getSibling(node)->right->color == BLACK)) {
            getSibling(node)->color = RED;
            node->parent->color = BLACK;
        }
        else
            delete_case5(node);
    }

    void delete_case5(Node* node) {
        if (node == node->parent->left && getSibling(node)
            && getSibling(node)->color == BLACK
            && (getSibling(node)->left == NULL || getSibling(node)->left->color == RED)
            && (getSibling(node)->right == NULL || getSibling(node)->right->color == BLACK)) {
                getSibling(node)->color = RED;
                getSibling(node)->left->color = BLACK;
                rotateRight(getSibling(node));
            }
        else if (node == node->parent->right
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