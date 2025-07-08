
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <string>

template <typename T> struct Node {
  T element;
  Node<T> *next;

  Node(T element) : element{element}, next{nullptr} {}
  Node(T element, Node<T> *next) : element{element}, next{next} {}
};

template <typename T>
std::string toString(const T& element) {
    return std::to_string(element);
}

std::string toString(const std::string& element) {
    return "\"" + element + "\"";
}

template <typename T> class List {
private:
  size_t m_size;
  Node<T> *m_head;

  // Feel free to add helper functions here, if necessary

public:
  // Constructs an empty container
  List() : m_size{0}, m_head{nullptr} {}

  // Constructs the container with the contents of the initializer list
  List(std::initializer_list<T> init_list) : m_size{0}, m_head{nullptr} {
    auto it = init_list.end();
    while (--it != init_list.begin()) {
      push_head(*it);
    }
    push_head(*it);
  }

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.

  // Destructor
  ~List() {
    // TODO: (Optional) Implement this method
  }

  // Copy constructor
  List(const List<T> &other) {
    // TODO: (Optional) Implement this method
  }

  // Copy assignment
  List<T> &operator=(const List<T> &other) {
    // TODO: (Optional) Implement this method
  }

  // Returns the contents of the head node
  const T& head() {
    if (m_size <= 0) {
      throw std::out_of_range("List is empty");
    }
    return m_head->element;
  }

  // Checks whether the container is empty
  bool empty() const { return m_size == 0; }

  // Returns the number of elements
  size_t size() const { return m_size; }

  // Inserts an element to the head
  void push_head(const T& element) {
    Node<T> *node = new Node<T>{element, m_head};
    m_head = node;
    m_size++;
  }

  // Removes the head element
  void pop_head() {
    if (m_size <= 0) {
      throw std::out_of_range("List is empty");
    }
    Node<T> *node = m_head;
    m_head = m_head->next;
    delete node;
    m_size--;
  }

  // Checks whether the container contains the specified element
  bool contains(const T& element) const {
      Node<T>* ptr = m_head;
      while (ptr != nullptr) {
          if (ptr->element == element) {
              return true;
          }
          ptr = ptr->next;
      }
      return false;
  }

  // Extracts the maximum element from the container, delete max element afterwards
  T extract_max() {
      if (empty()) {
          throw std::out_of_range("List is empty");
      }
      Node<T>* current = m_head;
      Node<T>* maxNode = m_head;
      Node<T>* prevMaxNode = nullptr;
      Node<T>* prev = nullptr;
      while (current != nullptr) {
          if (current->element > maxNode->element) {
              maxNode = current;
              prevMaxNode = prev;
          }
          prev = current;
          current = current->next;
      }

      if (maxNode == m_head) {
          m_head = m_head->next;
      }
      else {
          prevMaxNode->next = maxNode->next;
      }
      T maximum = maxNode->element;
      delete maxNode;
      m_size -= 1;
      return maximum;
  }

  // Reverse the container
  void reverse() {
      if (m_size < 2) {
          return;
      }
      Node<T>* prev = nullptr;
      Node<T>* current = m_head;
      Node<T>* next = nullptr;
      while (current != nullptr) {
          next = current->next;
          current->next = prev;
          prev = current;
          current = next;
      }
      m_head = prev;
  }

  // Returns a std::string equivalent of the container
  std::string to_string() const {
      if (empty()) {
          return "{}";
      }
      Node<T>* ptr = m_head;
      std::string container = "{" + toString(ptr->element);
      for (Node<T>* ptr = m_head->next; ptr != nullptr; ptr = ptr->next) {
          container = container + "," + " " + toString(ptr->element);
      }
      container += "}";
      return container;
  }

};

#endif
