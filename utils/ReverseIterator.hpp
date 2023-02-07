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
    ReverseIterator(iterator_type const ptr): _ptr(ptr){};

    template <typename It>
    ReverseIterator(const ReverseIterator<It> &copy) : _ptr(copy.getPtr()) {}

    ReverseIterator(const ReverseIterator& src) { *this = src; };

    template<class It>
    ReverseIterator& operator=(const ReverseIterator<It>& src) {
        _ptr = src._ptr;
        return (*this);
    }

    reference operator*() {
        iterator_type tmp = _ptr;
        return (*--tmp);
    }

    pointer operator->() {
        iterator_type tmp = _ptr;
        return &*--tmp;
    }

    iterator_type getPtr() const { return (_ptr); }

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

    // friend bool operator==(const ReverseIterator& lhs,
    //                         const ReverseIterator& rhs) {
    //     return lhs._ptr == rhs._ptr;
    // }

    // friend bool operator!=(const ReverseIterator& lhs,
    //                         const ReverseIterator& rhs) {
    //     return lhs._ptr != rhs._ptr;
    // }

    // friend bool operator>(const ReverseIterator& lhs,
    //                         const ReverseIterator& rhs) {
    //     return lhs._ptr < rhs._ptr;
    // }

    // friend bool operator>=(const ReverseIterator& lhs,
    //                         const ReverseIterator& rhs) {
    //     return lhs._ptr <= rhs._ptr;
    // }

    // friend bool operator<(const ReverseIterator& lhs,
    //                         const ReverseIterator& rhs) {
    // return lhs._ptr > rhs._ptr;
    // }

    // friend bool operator<=(const ReverseIterator& lhs,
    //                         const ReverseIterator& rhs) {
    //     return lhs._ptr >= rhs._ptr;
        // }

    template <class It>
    bool	operator==(const ReverseIterator<It> &rhs) const { return _ptr == rhs.getPtr(); }

    template <class It>
    bool	operator!=(const ReverseIterator<It> &rhs) const { return _ptr != rhs.getPtr(); }

    template <class It>
    bool	operator<(const ReverseIterator<It> &rhs) const { return _ptr > rhs.getPtr(); }

    template <class It>
    bool	operator>(const ReverseIterator<It> &rhs) const { return _ptr < rhs.getPtr(); };

    template <class It>
    bool	operator<=(const ReverseIterator<It> &rhs) const { return _ptr >= rhs.getPtr(); };

    template <class It>
    bool	operator>=(const ReverseIterator<It> &rhs) const { return _ptr <= rhs.getPtr(); };


private:
  iterator_type _ptr;

  };

} //namespace ft

#endif