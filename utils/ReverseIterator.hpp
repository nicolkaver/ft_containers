#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>

namespace ft {
template<typename T>
class ReverseIterator {
public:
    typedef typename std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    ReverseIterator() : _ptr(NULL){};
    ReverseIterator(pointer ptr) : _ptr(ptr){};
    ReverseIterator(const ReverseIterator& src) { *this = src; };

    ReverseIterator& operator=(const ReverseIterator& src) {
        _ptr = src._ptr;
        return *this;
    }

    reference operator*() { return *_ptr; }
    pointer operator->() { return _ptr; }

    const_reference operator*() const { return *_ptr; }
    const_pointer operator->() const { return _ptr; }

    ReverseIterator operator++() {
        --_ptr;
        return *this;
    }

    ReverseIterator operator++(int) {
        ReverseIterator tmp = *this;
        --_ptr;
        return tmp;
    }

    ReverseIterator operator--() {
        ++_ptr;
        return *this;
    }

    ReverseIterator operator--(int) {
        ReverseIterator tmp = *this;
        ++_ptr;
        return tmp;
    }

    ReverseIterator& operator+=(difference_type n) {
        _ptr -= n;
        return *this;
    }

    ReverseIterator operator+(difference_type n) {
        ReverseIterator copy = *this;
        copy += n;
        return copy;
    }

    ReverseIterator& operator-=(difference_type n) {
        _ptr += n;
        return *this;
    }

    ReverseIterator operator-(difference_type n) {
        ReverseIterator copy = *this;
        copy -= n;
        return copy;
    }

    friend difference_type operator-(const ReverseIterator& lhs,
                                    const ReverseIterator& rhs) {
        return rhs._ptr - lhs._ptr;
    }

    friend bool operator==(const ReverseIterator& lhs,
                            const ReverseIterator& rhs) {
        return lhs._ptr == rhs._ptr;
    }

    friend bool operator!=(const ReverseIterator& lhs,
                            const ReverseIterator& rhs) {
        return lhs._ptr != rhs._ptr;
    }

    friend bool operator>(const ReverseIterator& lhs,
                            const ReverseIterator& rhs) {
        return lhs._ptr < rhs._ptr;
    }

    friend bool operator>=(const ReverseIterator& lhs,
                            const ReverseIterator& rhs) {
        return lhs._ptr <= rhs._ptr;
    }

    friend bool operator<(const ReverseIterator& lhs,
                            const ReverseIterator& rhs) {
    return lhs._ptr > rhs._ptr;
    }

    friend bool operator<=(const ReverseIterator& lhs,
                            const ReverseIterator& rhs) {
        return lhs._ptr >= rhs._ptr;
    }

private:
  pointer _ptr;

  };

} //namespace ft

#endif