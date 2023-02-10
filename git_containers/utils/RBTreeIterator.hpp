#ifndef RED_BLACK_TREE_ITERATOR
#define RED_BLACK_TREE_ITERATOR

#include <iostream>
#include "Node.hpp"
#include "Pair.hpp"
#include "TypeTraits.hpp"
#include "RBTree.hpp"
#include "IteratorTraits.hpp"

namespace ft
{

    template <typename T>
    struct Node;

    template <typename T, typename U, bool isconst = false>
    struct RBTreeIterator
    {
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;

        // typedef U Node;

        typedef T value_type;
        typedef typename choose_type<isconst, const T &, T &>::type reference;
        typedef typename choose_type<isconst, const T *, T *>::type pointer;
        typedef typename choose_type<isconst,
                                     const U *, U *>::type nodeptr;

        // typedef value_type* pointer;
        // typedef value_type& reference;

        RBTreeIterator() : _ptr(NULL) {}
        // RBTreeIterator(Node* ptr): _ptr(ptr) {}
        RBTreeIterator(nodeptr ptr) : _ptr(ptr) {}
        RBTreeIterator(RBTreeIterator<T, U, false> const &src) : _ptr(src._ptr) {}
        RBTreeIterator(RBTreeIterator<T, U, true> const &src) : _ptr(src._ptr) {}
        virtual ~RBTreeIterator() {}

        RBTreeIterator &operator=(RBTreeIterator<T, U, isconst> const &rhs)
        {
            if (this != &rhs)
                this->_ptr = rhs._ptr;
            return (*this);
        }

        // template <typename T1, typename U1, iconst>
        // RBTreeIterator(const RBTreeIterator<T1, U1>& other) : _ptr(other.getPtr()){};

        nodeptr getPtr(void) const { return (_ptr); }

        // friend bool operator==(const RBTreeIterator &lhs,
        //                        const RBTreeIterator &rhs)
        // {
        //     return (lhs._ptr == rhs._ptr);
        // }
        // friend bool operator!=(const RBTreeIterator &lhs,
        //                        const RBTreeIterator &rhs)
        // {
        //     return (lhs._ptr != rhs._ptr);
        // }

        // friend bool operator>(const RBTreeIterator &lhs,
        //                       const RBTreeIterator &rhs)
        // {
        //     return lhs._ptr > rhs._ptr;
        // }

        // friend bool operator>=(const RBTreeIterator &lhs,
        //                        const RBTreeIterator &rhs)
        // {
        //     return lhs._ptr >= rhs._ptr;
        // }

        // friend bool operator<(const RBTreeIterator &lhs,
        //                       const RBTreeIterator &rhs)
        // {
        //     return lhs._ptr < rhs._ptr;
        // }

        // friend bool operator<=(const RBTreeIterator &lhs,
        //                        const RBTreeIterator &rhs)
        // {
        //     return lhs._ptr <= rhs._ptr;
        // }

        bool      operator == (const RBTreeIterator &rhs) const   { return _ptr == rhs._ptr; };
        bool      operator != (const RBTreeIterator &rhs) const   { return _ptr != rhs._ptr; };

        reference operator*() { return (_ptr->data); }

        pointer operator->() { return (&(_ptr->data)); }

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        RBTreeIterator operator++()
        {
            _ptr = getSuccessor(_ptr);
            return *this;
        }

        RBTreeIterator operator++(int)
        {
            RBTreeIterator tmp = *this;
            operator++();
            return tmp;
        }

        RBTreeIterator operator--()
        {
            _ptr = getPredecessor(_ptr);
            return *this;
        }

        RBTreeIterator operator--(int)
        {
            RBTreeIterator tmp = *this;
            operator--();
            return tmp;
        }

        nodeptr getMinValue(nodeptr node)
        {
            while (node && node->left)
                node = node->left;
            return (node);
        }

        nodeptr getMaxValue(nodeptr node)
        {
            while (node && node->right)
                node = node->right;
            return (node);
        }

        // Node *getSuccessor(Node *node)
        // {
        //     // if (node == NULL)
        //     //    return (NULL);
        //     if (node->right != NULL)
        //     {
        //         return (getMinValue(node->right));
        //     }
        //     else
        //     {
        //         Node *parent = node->parent;
        //         // while (node->data > parent->data)
        //         //         parent = parent->parent;
        //         while (parent && node == parent->right)
        //         {
        //             node = parent;
        //             parent = parent->parent;
        //         }
        //         return (parent);
        //     }
        // }

        // Node *getPredecessor(Node *node)
        // {
        //     // if (node == NULL)
        //     //     return (NULL);
        //     Node *parent = node->parent;
        //     if (node->left)
        //         return (getMaxValue(node->left));
        //     // while (node->data < parent->data)
        //     //     parent = parent->parent;
        //     while (parent && node == parent->left)
        //     {
        //         node = parent;
        //         parent = parent->parent;
        //     }
        //     return (parent);
        // }

        nodeptr getSuccessor(nodeptr node)
        {
            if (node->right != NULL)
                return (getMinValue(node->right));
            else
            {
                nodeptr parent = node->parent;
                // while (node->data > parent->data)
                //         parent = parent->parent;
                while (parent && node == parent->right)
                {
                    node = parent;
                    parent = parent->parent;
                }
                return (parent);
            }
        }

        nodeptr getPredecessor(nodeptr node)
        {
            nodeptr parent = node->parent;
            if (node->left) {
                return (getMaxValue(node->left));
            }
            // while (node->data < parent->data)
            //     parent = parent->parent;
            while (parent && node == parent->left)
            {
                node = parent;
                parent = parent->parent;
            }
            return (parent);
        }

        // Node* _ptr;
        nodeptr _ptr;
    };

} // namespace ft

#endif