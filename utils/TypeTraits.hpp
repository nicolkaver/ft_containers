#ifndef TYPE_TRAITS
# define TYPE_TRAITS

#include <iostream>

namespace ft {

//ENABLE_IF

template <bool condition, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

// IS_INTEGRAL

template <typename>
struct is_integral : std::__false_type {};

template <>
struct is_integral<bool> : std::__true_type {};
template <>
struct is_integral<char> : std::__true_type {};
template <>
// struct is_integral<char16_t> : std::__true_type {};
// template <>
// struct is_integral<char32_t> : std::__true_type {};
// template <>
struct is_integral<signed char> : std::__true_type {};
template <>
struct is_integral<short int> : std::__true_type {};
template <>
struct is_integral<int> : std::__true_type {};
template <>
struct is_integral<long int> : std::__true_type {};
template <>
struct is_integral<unsigned char> : std::__true_type {};
template <>
struct is_integral<unsigned short int> : std::__true_type {};
template <>
struct is_integral<unsigned int> : std::__true_type {};
template <>
struct is_integral<unsigned long int> : std::__true_type {};

} //namespace ft

#endif