
#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

#define RED 1
#define BLACK 0

namespace ft {

template <typename T>
struct Node {
  Node(T data)
      : data(data), parent(NULL), left(NULL), right(NULL), color(RED){};
  T data;
  Node<T> *parent;
  Node<T> *left;
  Node<T> *right;
  int color;
};

}  // namespace ft

#endif