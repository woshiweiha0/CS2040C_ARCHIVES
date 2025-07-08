#pragma once
#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

using std::string;

template <typename T>
std::string my_to_string(const T& t) {
  return std::to_string(t);
}

template <>
std::string my_to_string(const std::string& t) {
  return "\"" + t + "\"";
}

template <typename T> struct Node {
  T element;
  int height;
  Node<T> *left;
  Node<T> *right;

  Node(T element)
      : element{element}, height{0}, left{nullptr}, right{nullptr} {}
  Node(T element, int height)
      : element{element}, height{height}, left{nullptr}, right{nullptr} {}
};

template <typename T> class Tree {
private:
  size_t m_size;
  Node<T> *m_root;

public:
  // Constructor
  Tree();

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.

  // Destructor
  ~Tree();

  // Returns a pointer to the root
  Node<T> *root();

  // Checks whether the tree is empty
  bool empty() const;

  // Returns the number of elements
  size_t size() const;

  // Returns the height of the tree
  int height() const;

  // Inserts the specified element
  void insert(T element);

  // Checks whether the container contains the specified element
  bool contains(T element) const;

  // Returns the maximum element
  T max() const;

  // Returns the minimum element
  T min() const;

  // Returns the successor of the specified element
  T successor(T element);

  // Convert each element in the tree to string in pre-order.
  string pre_order();

  // Convert each element in the tree to string in order.
  string in_order();

  // Convert each element in the tree to string in post-order.
  string post_order();

  // Returns a string equivalent of the tree
  string to_string(bool with_height = true) const {
    return m_to_string(with_height, m_root, 0);
  }

private:
  string m_to_string(bool with_height, Node<T> *node, int ident) const {
    string res;
    if (node == nullptr) {
      return res;
    }
    if (node->right != nullptr) {
      res += m_to_string(with_height, node->right, ident + 2);
    }
    for (int i = 0; i < ident; i++) {
      res += " ";
    }
    res += my_to_string(node->element);
    if (with_height) {
      res += "(h=" + my_to_string(node->height) + ")";
    }
    res += "\n";
    if (node->left != nullptr) {
      res += m_to_string(with_height, node->left, ident + 2);
    }
    return res;
  }

  // Feel free to declare helper functions here, if necessary [HELPER]
  
  // Recursively delete Tree by deleting the left and right children then its parent
  void deleteNodes(Node<T>* node) {
      if (node) {
          deleteNodes(node->left);
          deleteNodes(node->right);
          node->left = nullptr;
          node->right = nullptr;
          delete node;
      }
      return;
  }

  // Returns height of a given node
  int getHeight(Node<T>* node) const {
      if (node == nullptr) {
          return -1;
      }
      return node->height;
  }

  // Returns height difference between the 2 children of a given node
  int childHeightDiff(Node<T>* node) const {
      if (node == nullptr) {
          return -1;
      }
      int leftHeight = getHeight(node->left);
      int rightHeight = getHeight(node->right);
      return leftHeight - rightHeight;
  }

  Node<T>* rightRotate(Node<T>* y) {
      Node<T>* x = y->left;
      Node<T>* t = x->right;
      x->right = y;
      y->left = t;
      y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
      x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
      return x;
  }

  Node<T>* leftRotate(Node<T>* x) {
      Node<T>* y = x->right;
      Node<T>* t = y->left;
      y->left = x;
      x->right = t;
      x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
      y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
      return y;
  }

  // Insert element and balance the tree
  Node<T>* insertElement(Node<T>* node, T element) {
      if (node == nullptr) {
          return new Node<T>(element, 0);
      }
      if (element < node->element) {
          node->left = insertElement(node->left, element);
      }
      else {
          node->right = insertElement(node->right, element);
      }
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

      int heightDiff = childHeightDiff(node);

      // Left Left Case
      if (heightDiff > 1 && (element <= node->left->element)) {
          return rightRotate(node);
      }
      // Right Right Case
      if (heightDiff < -1 && (element > node->right->element)) {
          return leftRotate(node);
      }
      // Left Right Case
      if (heightDiff > 1 && (element > node->left->element)) {
          node->left = leftRotate(node->left);
          return rightRotate(node);
      }
      // Right Left Case
      if (heightDiff < -1 && (element <= node->right->element)) {
          node->right = rightRotate(node->right);
          return leftRotate(node);
      }
      return node;
  }

  };

// Constructor
template <typename T> Tree<T>::Tree() {
    // TODO: Implement this method
    m_size = 0;
    m_root = nullptr;
}

// Destructor
template <typename T> Tree<T>::~Tree() {
    // TODO: Implement this method
    deleteNodes(m_root);
    m_root = nullptr;
    m_size = 0;
}

// Returns a pointer to the root
template <typename T> Node<T> *Tree<T>::root() {
    // TODO: Implement this method
    return m_root;
}

// Checks whether the tree is empty
template <typename T> bool Tree<T>::empty() const {
    // TODO: Implement this method
    return (m_size == 0);
}

// Returns the number of elements
template <typename T> size_t Tree<T>::size() const {
    // TODO: Implement this method
    return m_size;
}

// Returns the height of the tree
template <typename T> int Tree<T>::height() const {
    // TODO: Implement this method
    return getHeight(m_root);
}

// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
    // TODO: Implement this method
    m_root = insertElement(m_root, element);
    m_size += 1;
}

// Checks whether the container contains the specified element
template <typename T> bool Tree<T>::contains(T element) const {
    // TODO: Implement this method
    Node<T>* current = m_root;
    while (current != nullptr) {
        if (element < current->element) {
            current = current->left;
        }
        else if (element > current->element) {
            current = current->right;
        }
        else {
            return true;
        }
    }
    return false;
}

// Returns the maximum element
template <typename T> T Tree<T>::max() const {
    // TODO: Implement this method
    if (empty()) {
        throw std::out_of_range("Tree is empty");
    }
    Node<T>* current = m_root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->element;
}

// Returns the minimum element
template <typename T> T Tree<T>::min() const {
    // TODO: Implement this method
    if (empty()) {
        throw std::out_of_range("Tree is empty");
    }
    Node<T>* current = m_root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->element;
    
}

// Returns the successor of the specified element
template <typename T> T Tree<T>::successor(T element) {
    // TODO: Implement this method
    if (empty()) {
        throw std::out_of_range("Tree is empty");
    }
    Node<T>* current = m_root;
    Node<T>* succ = nullptr;
    
    while (current != nullptr) {
        if (element < current->element) {
            succ = current;
            current = current->left;
        }
        else if (element > current->element) {
            current = current->right;
        }
        else {
            if (current->right != nullptr) {
                current = current->right;
                while (current->left != nullptr) {
                    current = current->left;
                }
                return current->element;
            }
            break;
        }
    }
    
    if (succ == nullptr) {
        throw std::out_of_range("No successor found");
    }
    return succ->element;
}

template <typename T>
string _pre_order(Node<T> *node) {
  return my_to_string(node->element)
    + (node->left == nullptr ? "" : " " + _pre_order(node->left))
    + (node->right == nullptr ? "" : " " + _pre_order(node->right));
}

template <typename T>
string Tree<T>::pre_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _pre_order(m_root);
}

template <typename T>
string _in_order(Node<T>* node) {
    return (node->left == nullptr ? "" : _in_order(node->left) + " ")
        + my_to_string(node->element)
        + (node->right == nullptr ? "" : " " + _in_order(node->right));
}

template <typename T>
string Tree<T>::in_order() {
    // TODO: Implement this method
    if (m_root == nullptr) {
        return "";
    }
    return _in_order(m_root);
}

template <typename T>
string _post_order(Node<T>* node) {
    return (node->left == nullptr ? "" : _post_order(node->left) + " ")
        + (node->right == nullptr ? "" : _post_order(node->right) + " ")
        + my_to_string(node->element);
}

template <typename T>
string Tree<T>::post_order() {
    // TODO: Implement this method
    if (m_root == nullptr) {
        return "";
    }
    return _post_order(m_root);
}

#endif
