#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>

namespace ft {
template<class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
class map {
public:
    typedef Key key_value;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef Compare key_compare;
    // value_compare
    typedef Allocator allocator_type;
    typedef allocator_type::reference reference;
    typedef allocator_type::const_reference const_reference;
    typedef allocator_type::pointer pointer;
    typedef allocator_type::const_pointer;

    typedef ft::RBTreeIterator<T> iterator;
    typedef ft::RBTreeIterator<const T> const_iterator;
    typedef ft::RBTreeReverseIterator<T> reverse_iterator;
    typedef ft::RBTreeReverseIterator<const T> const_reverse_iterator;

    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

// CONSTRUCTORS
    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
    : _size(0), _compare(comp), _allocator(alloc), _treeAllocator(), _RBTreeMap() {}

    template <class InputIt>  
    map (InputIt first, InputIt last, const key_compare& comp = key_compare(), 
            const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
        : _size(0), _compare(comp), _allocator(alloc), 

    map (const map& src) { *this = src; }

    ~map() {}

    map & operator=(const map & rhs) {
        _size = rhs._size;
        _compare = rhs._compare;
        _allocator = rhs._allocator;
        _treeAllocator = rhs._treeAllocator;
        _rbtree = rhs._rbtree;
        return (*this);
    }

//ITERATORS
    iterator begin() { return (iterator(_rbtree)); }

    const_iterator begin() const { return (iterator(_rbtree)); }

    iterator end() { return (iterator(_rbtree + _size)); }

    const_iterator end() const { return (iterator(_rbtree + _size)); }

    reverse_iterator rbegin() { return (iterator(_rbtree + _size - 1)); }
    


private:
    size_type _size;
    key_compare _compare;
    allocator_type _allocator;
    treeAllocator _treeAllocator;
    RBTreeMap<value_type, key_compare, allocator_type>* _rbtree;

};


} //namespace ft

#endif