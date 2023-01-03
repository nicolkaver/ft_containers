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
    typedef ft::RandomAccessIterator<const T> const_iterator;
    typedef ft::ReverseIterator<T> reverse_iterator;
    typedef ft::ReverseIterator<const T> const_reverse_iterator;

    vector(void): _arr(NULL), _size(0), _capacity(0) {};
    explicit vector (const allocator_type& alloc): _arr(NULL), _size(0), _capacity(0), _allocator(alloc) {};
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
        difference_type range = last - first;
        reserve(range);
        _size = range;
        for (size_type i = 0; i < size(); i++) {
            _allocator.construct(_arr + i, *(first++));
        }
    }

    vector(const vector & src) : _arr(NULL), _size(0), _capacity(0) { *this = src; };

    ~vector() {
        clear();
        _allocator.deallocate(_arr, capacity());
    }

    vector & operator=(const vector& other) {
        clear();
        reserve(other.capacity());
        _size = other.size();
        _allocator = other._allocator;
        for (size_type i = 0; i < size(); i++) {
            _allocator.construct(_arr + i, other._arr[i]);
        }
        return (*this);
    }

    void assign(size_type count, value_type const & value) {
        if (count > capacity()) {
            reserve(count);
        }
        for (size_type i = 0; i < count; ++i) {
            _allocator.construct(_arr + i, value);
        }
        _size = count;
    };

    template <class InputIt>
    void assign(InputIt first, InputIt last,
                typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                        InputIt>::type* = NULL) {
        size_type count = static_cast<size_type>(std::distance(first, last));
        if (count > capacity()) {
            reserve(count);
        }
        for (size_type i = 0; i < count; ++i) {
            _allocator.construct(_arr + i, *(first++));
        }
        _size = count;
    }

    allocator_type get_allocator() const { return (_allocator); }

// ELEMENT ACCESS

    reference at( size_type pos ) {
        if (!(pos < size()))
            throw std::out_of_range("Error: pos is out of range.");
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

    reference back() { return (*_arr + _size - 1); }

    const_reference back() const { return (*_arr + _size - 1); }

    T* data() { return (_arr); }

    const T* data() const { return (_arr); }

//ITERATORS

    iterator begin() { return (iterator(_arr)); }

    const_iterator begin() const { return (const_iterator(_arr)); }

    iterator end() { return (iterator(*_arr + _size)); }

    const_iterator end() const { return (const_iterator(*_arr + _size)); }

    reverse_iterator rbegin() { return (reverse_iterator(_arr + _size - 1)); }

    const_reverse_iterator rbegin() const { return (const_reverse_iterator(_arr + _size - 1)); }

    reverse_iterator rend() { return (reverse_iterator(_arr - 1)); }

    const_reverse_iterator rend() const { return (const_reverse_iterator(_arr - 1)); }

// CAPACITY

    bool empty() const { return (_size == 0); }

    size_type size() const { return (_size); }

    size_type max_size() const { return (std::numeric_limits<difference_type>::max()); }

    void reserve( size_type new_cap ) {
        if (new_cap <= capacity())
            return ;
        if (new_cap > max_size())
            throw std::length_error("Error: New capacity is greater than the container's limit");
        T* newArray = _allocator.allocate(new_cap);
        for (size_t i = 0; i < _size; i++) {
            _allocator.construct(newArray + i, _arr[i]);
            _allocator.destroy(_arr + i);
        }
        _allocator.deallocate(_arr, _capacity);
        _capacity = new_cap;
        _arr = newArray;
    }

    size_type capacity() const { return (_capacity); }

// MODIFIERS

    void clear() { 
        for (size_t i = 0; i < _size; i++)
            _allocator.destroy(_arr + i);
        _size = 0;
    }

    iterator insert( const_iterator pos, const T& value ) {
        size_type i = static_cast<size_type>(std::distance(begin(), pos));
        insert(pos, 1, value);
        return (iterator(_arr + i));
    }

    iterator insert( const_iterator pos, size_type count, const T& value ) {
        difference_type oldEndPos = this->end() - this->begin();
        difference_type position = pos - this->begin();
        iterator oldEndIt;
        iterator endIt;

        resize(_size + count);
        oldEndIt = this->begin() + oldEnd
    }

    // iterator erase( iterator pos ) { }

    // iterator erase( iterator first, iterator last ) { }

    // void push_back( const T& value ) { }

    // void pop_back() { }

    // void resize( size_type count ) { }

    // void resize( size_type count, T value = T() ) { }

    void swap( vector & other ) {
        vector swapArr;

        swapArr._arr = this->_arr;
        swapArr._size = this->_size;
        swapArr._capacity = this->_capacity;
        swapArr._allocator = this->_allocator;

        this->_arr = other._arr;
        this->_size = other._size;
        this->_capacity = other._capacity;
        this->_allocator = other._allocator;

        other._allocator = swapArr._allocator;
        other._size = swapArr._size;
        other._capacity = swapArr._capacity;
        other._allocator = swapArr._allocator;
    }

    friend bool operator==( const vector<T,Allocator>& lhs,
                            const vector<T,Allocator>& rhs ) {
        return (equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    friend bool operator!=( const vector<T,Allocator>& lhs,
                            const vector<T,Allocator>& rhs ) {
        return (equal(lhs.begin(), lhs.end(), rhs.begin()) == false);
    }

    friend bool operator<( const vector<T,Allocator>& lhs,
                            const vector<T,Allocator>& rhs ) {
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    // friend bool operator<=( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs ) {
        
    // }

    // friend bool operator>( const std::vector<T,Alloc>& lhs,
    //             const std::vector<T,Alloc>& rhs ) {

    // }

    // friend bool operator>=( const std::vector<T,Alloc>& lhs,
    //              const std::vector<T,Alloc>& rhs ) {
                
    // }

    friend void swap( vector<T,Allocator>& lhs, vector<T,Allocator>& rhs ) { 
        vector swapArr;

        swapArr._arr = lhs._arr;
        swapArr._size = lhs._size;
        swapArr._capacity = lhs._capacity;
        swapArr._allocator = lhs._allocator;

        lhs._arr = rhs._arr;
        lhs._size = rhs._size;
        lhs._capacity = rhs._capacity;
        lhs._allocator = rhs._allocator;

        rhs._allocator = swapArr._allocator;
        rhs._size = swapArr._size;
        rhs._capacity = swapArr._capacity;
        rhs._allocator = swapArr._allocator;
    }

private:
    pointer _arr;
    size_type _size;
    size_type _capacity;
    allocator_type _allocator;
};

} // namespace ft

#endif