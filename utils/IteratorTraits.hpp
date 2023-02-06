#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iostream>

namespace ft {

template <class Iter>
struct iterator_traits {
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
    typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef value_type& pointer;
    typedef value_type& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const value_type& const_pointer;
    typedef const value_type& const_reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <bool flag, class const_type, class normal_type>
struct choose_type;

template <class const_type, class normal_type>
struct choose_type<true, const_type, normal_type> {
    typedef const_type type;
};

template <class const_type, class normal_type>
struct choose_type<false, const_type, normal_type> {
    typedef normal_type type;
};

} // namespace ft

#endif