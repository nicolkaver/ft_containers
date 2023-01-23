#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <limits>

# include "../utils/Pair.hpp"
# include "../utils/RBTree.hpp"
# include "../utils/RBTreeIterator.hpp"
# include "../utils/RBTreeReverseIterator.hpp"
# include "../utils/TypeTraits.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/IteratorTraits.hpp"

namespace ft {
template<typename Key, typename T, class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
    typedef Key key_value;
    typedef T mapped_type;
    typedef ft::pair<const Key, T> value_type;
    typedef Compare key_compare;
    
    class value_compare {
        friend class map;
    protected:
        Compare comp;
        value_compare (Compare c) : comp(c) {}
    public:
        bool operator() (const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };

    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    typedef typename allocator_type::template rebind<
        RBTree<value_type, key_compare, allocator_type> >::other treeAllocator;

    typedef typename ft::RBTree<value_type, key_compare, allocator_type>::iterator iterator;
    typedef typename ft::RBTree<value_type, key_compare,
                                    allocator_type>::const_iterator const_iterator;
    typedef typename ft::RBTree<value_type, key_compare,
                                    allocator_type>::reverse_iterator reverse_iterator;
    typedef typename ft::RBTree<value_type, key_compare,
                                    allocator_type>::const_reverse_iterator const_reverse_iterator;

    typedef std::size_t size_type;
    typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

    //typedef std::ptrdiff_t difference_type;

// CONSTRUCTORS
    // map(): _size(0), _compare(key_compare()), _allocator(allocator_type()),
    //         _treeAllocator(treeAllocator()), _rbtree(NULL) {
    //     _rbtree = _treeAllocator.allocate(1);
    //     _treeAllocator.construct(_rbtree, RBTree<value_type, key_compare, allocator_type>());
    // }

    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
    : _size(0), _compare(comp), _allocator(alloc), _treeAllocator(treeAllocator()), _rbtree(NULL) {
        _rbtree = _treeAllocator.allocate(1);
        _treeAllocator.construct(_rbtree, RBTree<value_type, key_compare, allocator_type>());
    }

    template <class InputIt>  
    map(InputIt first, InputIt last, const key_compare& comp = key_compare(), 
            const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
        : _size(0), _compare(comp), _allocator(alloc), _treeAllocator(treeAllocator()), _rbtree(NULL) {
        _rbtree = _treeAllocator.allocate(1);
        _treeAllocator.construct(_rbtree, RBTree<value_type, key_compare, allocator_type>());
        insert(first, last);
    }

    map (const map& src): _size(0), _compare(src._compare), _allocator(src._allocator),
                        _treeAllocator(treeAllocator()), _rbtree(NULL) { *this = src; }

    ~map() {
            _treeAllocator.destroy(_rbtree);
            _treeAllocator.deallocate(_rbtree, 1);
    }

    map & operator=(const map & rhs) {
        if (this != &rhs) {
            _treeAllocator.destroy(_rbtree);
            _treeAllocator.deallocate(_rbtree, 1);
            _rbtree = _treeAllocator.allocate(1);
            _treeAllocator.construct(_rbtree, RBTree<value_type, key_compare, allocator_type>());
            _size = rhs._size;
            _compare = rhs._compare;
            _allocator = rhs._allocator;
            _treeAllocator = rhs._treeAllocator;
            *_rbtree = *(rhs._rbtree);
        }
        return (*this);
    }

//ITERATORS
    iterator begin() { return (_rbtree->begin()); }

    const_iterator begin() const { return (_rbtree->begin()); }

    iterator end() { return (_rbtree->end()); }

    const_iterator end() const { return (_rbtree->end()); }

    reverse_iterator rbegin() { return (_rbtree->rbegin()); }
    
    const_reverse_iterator rbegin() const { return (_rbtree->rbegin()); }

    reverse_iterator rend() { return (_rbtree->rend()); }

    const_reverse_iterator rend() const { return (_rbtree->rend()); }

//CAPACITY

    bool empty() const { return (_size == 0); }

    size_type size() const { return (_size); }

    size_type max_size() const {
        return (std::numeric_limits<difference_type>::max());
    }

//MODIFIERS

    void clear() {
        _rbtree->clear();
        _size = 0;
    }

    ft::pair<iterator,bool> insert (const value_type& val) {
        iterator pair = find(val.first);
        if (pair != end())
            return (ft::make_pair<iterator, bool>(pair, false));
        _size++;
        pair = iterator(_rbtree->insertNode(val));
        return (ft::make_pair<iterator, bool>(pair, true));
    }

    iterator insert (iterator position, const value_type& val) {
        (void)position;
        insert(val);
        iterator it = find(val.first);
        return (it);
    }

    template< class InputIt >
    void insert( InputIt first, InputIt last,
                    typename ft::enable_if<!ft::is_integral<InputIt>::val,
                                     InputIt>::type* = NULL ) {
        while (first != last) {
            insert(*first);
            *first++;
        }
    }

    void erase (iterator position) {
        _rbtree->deleteNode(position->first);
        _size--;
    }

    size_type erase (const key_value& k){
        iterator it = find(k);
        if (it == end())
            return (0);
        erase(k);
        return (1);
    }

    void erase (iterator first, iterator last) {
        while (first != last)
            erase(first++);
    }

    void swap (map& x) {
        size_type swapSize = _size;
        key_compare swapCompare = _compare;
        allocator_type swapAllocator = _allocator;
        treeAllocator swapTreeAllocator = _treeAllocator;
        RBTree<value_type, key_compare, allocator_type>* swapRBTree = _rbtree;

        _size = x._size;
        _compare = x._compare;
        _allocator = x._allocator;
        _treeAllocator = x._treeAllocator;
        _rbtree = x._rbtree;

        x._size = swapSize;
        x._compare = swapCompare;
        x._allocator = swapAllocator;
        x._treeAllocator = swapTreeAllocator;
        x._rbtree = swapRBTree;
    }

// LOOKUP

    size_type count (const key_value& k) const {
        iterator it = find(k);
        if (it == end())
            return (0);
        return (1);
    }

    iterator find (const key_value& k) {
        return (_rbtree->search(k));
    }
    
    const_iterator find (const key_value& k) const {
        return (_rbtree->search(k));
    }

    ft::pair<const_iterator,const_iterator> equal_range (const key_value& k) const {
        return (ft::make_pair(lower_bound(k), upper_bound(k)));
    }
    
    ft::pair<iterator,iterator> equal_range (const key_value& k) {
        return (ft::make_pair(lower_bound(k), upper_bound(k)));
    }

    iterator lower_bound (const key_value& k) { return (_rbtree->lower_bound(k)); }
    
    const_iterator lower_bound (const key_value& k) const { return (_rbtree->lower_bound(k)); }

    iterator upper_bound (const key_value& k) { return (_rbtree->upper_bound(k)); }
    
    const_iterator upper_bound (const key_value& k) const { return (_rbtree->upper_bound(k)); }

// get allocator

    allocator_type get_allocator() const { return (_allocator); }

// OBSERVERS

    key_compare key_comp() const { return (_compare); }

    value_compare value_comp() const { return (ft::map<key_value, mapped_type>::value_compare::comp); }

// ELEMENT ACCESS

    mapped_type& operator[] (const key_value& k) {
        iterator ret = _rbtree->search(k);
        if (ret == end())
            return ((*(insert(ft::make_pair(k, mapped_type())).first)).second);
        return ((*ret).second);
    }

    mapped_type& at (const key_value& k) {
        iterator ret = _rbtree->search(k);
        if (ret == end())
            throw std::out_of_range("Error: Key not found.");
        return ((*ret).second);
    }
    
    const mapped_type& at (const key_value& k) const {
        iterator ret = _rbtree->search(k);
        if (ret == end())
            throw std::out_of_range("Error: Key not found.");
        return ((*ret).second);
    }

// NON-MEMBER FUNCTIONS

    friend bool operator==(const map<Key, T, Compare, allocator_type>& lhs,
                         const map<Key, T, Compare, allocator_type>& rhs) {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator!=(const map<Key, T, Compare, allocator_type>& lhs,
                            const map<Key, T, Compare, allocator_type>& rhs) {
        return !operator==(lhs, rhs);
    }

    friend bool operator<(const map<Key, T, Compare, allocator_type>& lhs,
                            const map<Key, T, Compare, allocator_type>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
    }

    friend bool operator<=(const map<Key, T, Compare, allocator_type>& lhs,
                            const map<Key, T, Compare, allocator_type>& rhs) {
        return !(operator<(rhs, lhs));
    }

    friend bool operator>(const map<Key, T, Compare, allocator_type>& lhs,
                            const map<Key, T, Compare, allocator_type>& rhs) {
        return operator<(rhs, lhs);
    }
  
    friend bool operator>=(const map<Key, T, Compare, allocator_type>& lhs,
                            const map<Key, T, Compare, allocator_type>& rhs) {
        return !(operator<(lhs, rhs));
    }

    friend void swap(map<Key, T, Compare, allocator_type>& lhs,
                    map<Key, T, Compare, allocator_type>& rhs) {
        lhs.swap(rhs);
    }


private:
    size_type _size;
    key_compare _compare;
    allocator_type _allocator;
    treeAllocator _treeAllocator;
    RBTree<value_type, key_compare, allocator_type>* _rbtree;

};


} //namespace ft

#endif