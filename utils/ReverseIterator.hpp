#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <cstddef>
# include "IteratorTraits.hpp"

namespace ft {
template<typename Iter>
class ReverseIterator {
public:
    typedef Iter iterator_type;

    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::pointer pointer;
    typedef typename iterator_traits<iterator_type>::reference reference;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;

    ReverseIterator() : _ptr(NULL){};
    ReverseIterator(iterator_type const ptr) : _ptr(ptr){};
    ReverseIterator(const ReverseIterator& src) { *this = src; };

    ReverseIterator& operator=(const ReverseIterator& src) {
        _ptr = src._ptr;
        return (*this);
    }

    reference operator*() { return *_ptr; }
    // pointer operator->() { return _ptr; }
    pointer operator->() {
        iterator_type tmp = _ptr;
        return &*--tmp;
    }

    // const_reference operator*() const { return *_ptr; }
    // const_pointer operator->() const { return _ptr; }

    ReverseIterator operator++() {
        --_ptr;
        return (*this);
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
  iterator_type _ptr;

  };

} //namespace ft

#endif