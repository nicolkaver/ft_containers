#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>

namespace ft {
template<typename T>
class RandomAccessIterator {
public:
    typedef typename std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    RandomAccessIterator() : _ptr(NULL) {}
    RandomAccessIterator(pointer ptr) : _ptr(ptr) {}
    RandomAccessIterator(const RandomAccessIterator& other) { *this = other; }
    ~RandomAccessIterator() {}

    RandomAccessIterator& operator=(const RandomAccessIterator& other) {
        _ptr = other._ptr;
        return *this;
    }

    reference operator*() { return *_ptr; }
    pointer operator->() { return _ptr; }

    const_reference operator*() const { return *_ptr; }
    const_pointer operator->() const { return _ptr; }

    RandomAccessIterator operator++() {
        ++_ptr;
        return *this;
    }

    RandomAccessIterator operator++(int) {
        RandomAccessIterator tmp = *this;
        ++_ptr;
        return tmp;
    }

    RandomAccessIterator operator--() {
        --_ptr;
        return *this;
    }

    RandomAccessIterator operator--(int) {
        RandomAccessIterator tmp = *this;
        --_ptr;
        return tmp;
    }

    RandomAccessIterator& operator+=(difference_type n) {
        _ptr += n;
        return *this;
    }

    RandomAccessIterator operator+(difference_type n) {
        RandomAccessIterator copy = *this;
        copy += n;
        return copy;
    }

    RandomAccessIterator& operator-=(difference_type n) {
        _ptr -= n;
        return *this;
    }

    RandomAccessIterator operator-(difference_type n) {
        RandomAccessIterator copy = *this;
        copy -= n;
        return copy;
    }

    friend difference_type operator-(const RandomAccessIterator& lhs,
                                const RandomAccessIterator& rhs) {
        return lhs._ptr - rhs._ptr;
    }

    friend bool operator==(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
        return lhs._ptr == rhs._ptr;
    }
    friend bool operator!=(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
        return lhs._ptr != rhs._ptr;
    }

    friend bool operator>(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
        return lhs._ptr > rhs._ptr;
    }
    friend bool operator>=(const RandomAccessIterator& lhs,
                         const RandomAccessIterator& rhs) {
        return lhs._ptr >= rhs._ptr;
    }
    friend bool operator<(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
        return lhs._ptr < rhs._ptr;
    }
    friend bool operator<=(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
        return lhs._ptr <= rhs._ptr;
  }

private:
  pointer _ptr;
};

} // namespace ft

#endif