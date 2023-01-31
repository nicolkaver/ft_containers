#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include <iostream>

namespace ft {
template <class InputIterator1, class InputIterator2>
bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
    while (first1 != last1) {
        if (!(*first1 == *first2))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}


//true if the first range compares lexicographically less than the second.
//false otherwise (including when all the elements of both ranges are equivalent).

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1)
    {
        if (first2 == last2 || *first2 < *first1) 
            return false;
        else if (*first1 < *first2) 
            return true;
        ++first1;
        ++first2;
    }
    return true;
}

} // namespace ft

#endif