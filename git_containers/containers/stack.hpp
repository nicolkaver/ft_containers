#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include "../utils/randomAccessIterator.hpp"
# include "../utils/ReverseIterator.hpp"
# include "../utils/TypeTraits.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/IteratorTraits.hpp"

namespace ft {
template<typename T, class Container=ft::vector<T> >
class stack {
public:
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    explicit stack( const Container& cont = Container() ): c(cont) {}
    stack(stack const & src): c(src.c) {}
    ~stack() {}
    stack & operator=(stack const & rhs) {
        if (this != &rhs)
            this->c = rhs.c;
        return (*this);
    }

    //element access
    reference top(void) { return (c.back()); }
    const_reference top(void) const { return (c.back()); }

    //capacity functions
    bool empty(void) const { return (c.empty()); }
    size_type size(void) const { return (c.size()); }

    //modifiers
    void push( const value_type& value ) { c.push_back(value); }
    void pop() { c.pop_back(); }

    friend bool operator==(const stack<T, Container>& lhs,
                        const stack<T, Container>& rhs) {
    return (lhs.c == rhs.c);
    }

    friend bool operator!=(const stack<T, Container>& lhs,
                        const stack<T, Container>& rhs) {
    return (lhs.c != rhs.c);
    }

    friend bool operator<(const ft::stack<T, Container>& lhs,
                        const ft::stack<T, Container>& rhs) {
    return (lhs.c < rhs.c);
    }

    friend bool operator<=(const stack<T, Container>& lhs,
                        const stack<T, Container>& rhs) {
    return (lhs.c < rhs.c || lhs.c == rhs.c);
    }

    friend bool operator>(const ft::stack<T, Container>& lhs,
                        const ft::stack<T, Container>& rhs) {
    return (lhs.c > rhs.c);
    }

    friend bool operator>=(const ft::stack<T, Container>& lhs,
                         const ft::stack<T, Container>& rhs) {
    return (lhs.c >= rhs.c);
    }

protected:
    Container c;
};

} // namespace ft

#endif