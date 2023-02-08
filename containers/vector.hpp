#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <algorithm> // max, min, fill_n
# include <cstddef> // ptrdiff_t, size_t
# include <limits> // numeric_limits
# include <memory> // allocator

# include "../utils/randomAccessIterator.hpp"
# include "../utils/ReverseIterator.hpp"
# include "../utils/TypeTraits.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/IteratorTraits.hpp"

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector {
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
    
    typedef ft::RandomAccessIterator<T> iterator;
    typedef ft::RandomAccessIterator<T, true> const_iterator;
    typedef ft::ReverseIterator<iterator> reverse_iterator;
    typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

    vector(void): _arr(NULL), _size(0), _capacity(0) {};
    explicit vector (const allocator_type& alloc): _arr(NULL), _size(0), _capacity(0), _allocator(alloc) {}
    explicit vector(size_type n, const value_type& value = value_type(),
                    const allocator_type& alloc = allocator_type())
        : _arr(NULL), _size(0), _capacity(0), _allocator(alloc) {
        reserve(n);
        _size = n;
        _capacity = n;
        for (size_type i = 0; i < size(); i++) {
            _allocator.construct(_arr + i, value);
        }
    }

    template <class InputIt>
    vector(InputIt first, InputIt last,
            const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                    InputIt>::type* = NULL)
        : _arr(NULL), _size(0), _capacity(0), _allocator(alloc) {
        InputIt tmp = first;
        int range = 0;
        for (; tmp != last; tmp++)
            range++;
        // difference_type range = last - first;
        reserve(range);
        _size = range;
        for (size_type i = 0; i < size(); i++) {
            _allocator.construct(&_arr[i], *(first++));
        }
    }

    vector(const vector & src) : _arr(NULL), _size(0), _capacity(0) { *this = src; };

    ~vector() {
        clear();
        _allocator.deallocate(_arr, capacity());
    }

    vector & operator=(const vector& other) {
        if (this != &other) {
            clear();
            // reserve(other.capacity());
            _allocator.deallocate(_arr, _capacity);
            _size = other.size();
            _allocator = other._allocator;
            _capacity = other.capacity();
            _arr = _allocator.allocate(other.capacity());
            for (size_type i = 0; i < size(); i++) {
                _allocator.construct(&_arr[i], other._arr[i]);
            }
        }
        return (*this);
        // if (&other == this)
        //     return *this;
        // assign(other.begin(), other.end());
        // return *this;
    }

    void assign(size_type count, value_type const & value) {
        if (count > capacity())
            reserve(count);
        for (size_type i = 0; i < count; ++i) {
            _allocator.construct(_arr + i, value);
        }
        _size = count;
    };

    template <class InputIt>
    void assign(InputIt first, InputIt last,
                typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                    InputIt>::type* = NULL) {
        size_type count = 0;
        InputIt tmp = first;
        InputIt tmp2 = last;
        for (; tmp != tmp2; tmp++)
            count++;
        if (count > capacity())
            reserve(count);
        for (size_type i = 0; i < count; ++i) {
            _allocator.construct(_arr + i, *(first++));
        }
        _size = count;
    }

    allocator_type get_allocator() const { return (_allocator); }

// ELEMENT ACCESS

    reference at( size_type pos ) {
        if (!(pos < size()))
            throw std::out_of_range("Error: pos is out of range");
        return (_arr[pos]);
    }

    const_reference at( size_type pos ) const {
        if (!(pos < size()))
            throw std::out_of_range("Error: pos is out of range.");
        return (_arr[pos]);
    }

    reference operator[]( size_type pos ) { return (_arr[pos]); } //no checking like with .at

    const_reference operator[]( size_type pos ) const { return (_arr[pos]); }

    reference front() { return (*_arr); }

    const_reference front() const { return (*_arr); }

    reference back() { return (*(_arr + _size - 1)
    ); }

    const_reference back() const { return (*_arr + _size - 1); }

    T* data() { return (_arr); }

    const T* data() const { return (_arr); }

//ITERATORS

    iterator begin() { return (iterator(_arr)); }

    const_iterator begin() const { return (const_iterator(_arr)); }

    iterator end() { return (iterator(_arr + _size)); }

    const_iterator end() const { return (const_iterator(_arr + _size)); }

    reverse_iterator rbegin() { return (reverse_iterator(end())); }

    const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

    reverse_iterator rend() { return (reverse_iterator(begin())); }

    const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

// CAPACITY

    bool empty() const { return (_size == 0); }

    size_type size() const { return (_size); }

    size_type max_size() const { return (allocator_type().max_size()); }
    // size_type max_size() const { return (std::numeric_limits<difference_type>::max()); }

    void reserve( size_type n ) { 
        if (n > max_size())
            throw std::length_error("vector::reserve");
        if (n < _capacity)
            return;

        value_type *new_container = _allocator.allocate(n);

        for (size_type i = 0; i < _size; i++) {
            _allocator.construct(&new_container[i], _arr[i]);
            _allocator.destroy(&_arr[i]);
        }
        _allocator.deallocate(_arr, _capacity);
        _capacity = n;
        _arr = new_container;
    }

    size_type capacity() const { return (_capacity); }

    void resize( size_type count, T value = T() ) {
        if (count > max_size())
            throw std::length_error("Error: New capacity is greater than the container's limit");
        if (count < size()) {
            for (size_type i = count; i < size(); i++)
                _allocator.destroy(_arr + i);
        }
        else {
            reserve(count);
            for (size_type i = size(); i < count; i++) {
                push_back(value);
            }
        }
        _size = count;
    }

// MODIFIERS

    void clear() { 
        for (size_t i = 0; i < _size; i++)
            _allocator.destroy(_arr + i);
        _size = 0;
    }

    iterator insert( iterator pos, const T& value ) {
        //size_type i = static_cast<size_type>(std::distance(begin(), pos));
        size_t i = 0;
        iterator it = begin();
        for (; it != pos; it++)
            i++;
        if (pos == end()) {
            push_back(value);
            return (iterator(_arr + i));
        }
        insert(pos, 1, value);
        return (iterator(_arr + i));
    }

    void insert( iterator pos, size_type count, const T& value ) { //OK?
        if (count == 0)
            return ;

        if (pos == end()) {
            for (size_t i = 0; i < count; i++)
                push_back(value);
            return ;
        }
        vector<T, Allocator> tmp(pos, end());
        iterator it = tmp.begin();
        iterator ite = tmp.end();
        erase(pos, end());
        for (size_type i = 0; i < count; i++)
            push_back(value);
        for (; it != ite; it++) {
            push_back(*it);
        }
        // erase(tmp.begin(), tmp.end());
    }

    template <class InputIt>
    void insert (iterator pos, InputIt first, InputIt last,
                typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
        if (pos == end()) {
            for (; first != last; first++)
                push_back(*first);
        }
        vector<T, Allocator> tmp(pos, end());
        size_type count = 0;
        iterator it1 = first;
        for (; it1 != last; it1++)
            count++;
        if (count == 0)
            return ;
        iterator it = tmp.begin();
        iterator ite = tmp.end();
        erase(pos, end());
        for (; first != last; first++)
            push_back(*first);
        for (; it != ite; it++)
            push_back(*it);
    }

    iterator erase( iterator pos ) { //OK
        if (pos == end()) {
            pop_back();
            return (pos);
        }
        vector<T, Allocator> tmp(pos + 1, end());
        iterator it = tmp.begin();
        iterator ite = tmp.end();

        for (size_type i = 0; i <= tmp.size(); i++)
            pop_back();
        for (; it != ite; it++)
            push_back(*it);
        return (pos);
    }

    iterator erase( iterator first, iterator last ) {
        if (first == last)
            return (last);
        
        vector<T, Allocator> tmp1(first + 1, end());
        vector<T, Allocator> tmp2(last, end());
        iterator it = tmp2.begin();
        iterator ite = tmp2.end();

        for (size_type i = 0; i <= tmp1.size(); i++)
            pop_back();
        for (; it != ite; it++)
            push_back(*it);
        return (first);
    }

    void push_back( const T& value ) {
        if (size() == capacity() && capacity() > 0)
            reserve(capacity() * 2);
        else {
            if (_capacity == 0)
                reserve(1);
        }     
        _allocator.construct(_arr + _size, value);
        _size++;
    }

    void pop_back() {
        _allocator.destroy(_arr + _size - 1);
        _size--;
    }

    void swap( vector & other ) {
        pointer tmpArr = _arr;
        size_type tmpSize = _size;
        size_type tmpCapacity = _capacity;
        allocator_type tmpAlloc = _allocator;

        this->_arr = other._arr;
        this->_size = other._size;
        this->_capacity = other._capacity;
        this->_allocator = other._allocator;

        other._arr = tmpArr;
        other._size = tmpSize;
        other._capacity = tmpCapacity;
        other._allocator = tmpAlloc;
    }

    friend bool operator==( const vector<T,Allocator>& lhs,
                            const vector<T,Allocator>& rhs ) {
        // size_t i = 0;
        // if (lhs.size() != rhs.size())
        //     return (false);
        // while (i < lhs.size()) {
        //     if (lhs._arr[i] != rhs._arr[i])
        //         return false;
        // }
        // return true;


        size_t i = 0, j = 0;
        while (i < lhs.size() && j < rhs.size()) {
            if (lhs._arr[i++] != rhs._arr[j++]) {
                return false;
        }
        }
        return i == lhs.size() && j == rhs.size();

        //return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    friend bool operator!=( const vector<T,Allocator>& lhs,
                            const vector<T,Allocator>& rhs ) {
        return (!(lhs == rhs));
    }

    friend bool operator<( const vector<T,Allocator>& lhs,
                            const vector<T,Allocator>& rhs ) {
        // size_t i = 0;
        // while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i])
        //     i++;
        // return (i != rhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i]));
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    friend bool operator<=( const vector<T,Allocator>& lhs,
                    const vector<T,Allocator>& rhs ) {
        // size_t i = 0;
        // while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i])
        //     i++;
        // return ((i == rhs.size() && i == lhs.size()) ||
        //         (i != rhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i])));
        return (!(rhs < lhs));
    }

    friend bool operator>( const vector<T,Allocator>& lhs,
                const vector<T,Allocator>& rhs ) {
        size_t i = 0;
        while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i])
            i++;
        return (i != lhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i]));
        // return (rhs < lhs);
    }

    friend bool operator>=( const vector<T,Allocator>& lhs,
                 const vector<T,Allocator>& rhs ) {
        size_t i = 0;
        while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i])
            i++;
        return ((i == lhs.size() && i == rhs.size()) ||
                (i != lhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i])));
        // return (!(lhs < rhs));
    }

    friend void swap( vector<T, Allocator> & lhs, vector<T, Allocator> & rhs ) { 
        lhs.swap(rhs);
    }

private:
    pointer _arr;
    size_type _size;
    size_type _capacity;
    allocator_type _allocator;
};

} // namespace ft

#endif
