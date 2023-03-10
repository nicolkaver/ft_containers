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

template <typename T>
struct is_integral {
    static const bool value = false;
};

template <>
struct is_integral<bool> {
    static const bool value = true;
};

template <>
struct is_integral<char> {
    static const bool value = true;
};

// template <>
// struct is_integral<char16_t> : std::__true_type {};

// template <>
// struct is_integral<char32_t> : std::__true_type {};

template <>
struct is_integral<signed char> {
    static const bool value = true;
};

template <>
struct is_integral<short int> {
    static const bool value = true;
};

template <>
struct is_integral<int> {
    static const bool value = true;
};

template <>
struct is_integral<long int> {
    static const bool value = true;
};

template <>
struct is_integral<unsigned char> {
    static const bool value = true;
};

template <>
struct is_integral<unsigned short int> {
    static const bool value = true;
};

template <>
struct is_integral<unsigned int> {
    static const bool value = true;
};

template <>
struct is_integral<unsigned long int> {
    static const bool value = true;
};

// template <bool is_integral, typename T>
//         struct is_integral_res {
//             typedef T type;
//             static const bool value = is_integral;
//             };

//     /*
//     ** @brief default template of the structure is_integral_type.
//     ** If the type given in argument is from the list, the structure
//     ** will be overide by nexts, in according to it type.
//     ** If the type given is argument isn't in the list, 
//     ** stocked value will be false. So it's not a integral type.
//     */
//     template <typename>
//         struct is_integral_type : public is_integral_res<false, bool> {};

//     /* @brief is_integral_type for bool. "value is true".*/
//     template <>
//         struct is_integral_type<bool> : public is_integral_res<true, bool> {};

//     /* @brief is_integral_type for char. "value is true".*/
//     template <>
//         struct is_integral_type<char> : public is_integral_res<true, char> {};

//     /* @brief is_integral_type for signed char. "value is true".*/
//     template <>
//         struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

//     /* @brief is_integral_type for short int. "value is true".*/
//     template <>
//         struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    
//     /* @brief is_integral_type for int. "value is true".*/
//     template <>
//         struct is_integral_type<int> : public is_integral_res<true, int> {};

//     /* @brief is_integral_type for long int. "value is true".*/
//     template <>
//         struct is_integral_type<long int> : public is_integral_res<true, long int> {};

//     /* @brief is_integral_type for long long int. "value is true".*/
//     template <>
//         struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

//     /* @brief is_integral_type for unsigned char. "value is true".*/
//     template <>
//         struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

//     /* @brief is_integral_type for unsigned short int. "value is true".*/
//     template <>
//         struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

//     /* @brief is_integral_type for unsigned int. "value is true".*/
//     template <>
//         struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

//     /* @brief is_integral_type for unsigned long int. "value is true".*/
//     template <>
//         struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    
//     /* @brief is_integral_type for unsigned long long int. "value is true".*/
//     template <>
//         struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

//     /*
//     ** @brief Give a structure who contain is the
//     ** typename given in template is integral or not,
//     ** stocked in "value".
//     */
//     template <typename T>
//         struct is_integral : public is_integral_type<T> { };

} //namespace ft

#endif