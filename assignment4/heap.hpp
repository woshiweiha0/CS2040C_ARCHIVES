#pragma once
#include <math.h>
#include <stdexcept>
#include <string>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

#define DEFAULTHEAPSIZE 1023
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

template <class T>
class Heap {
 protected:
     T* _heap;
     int _size;

 public:
     Heap() { _heap = new T[DEFAULTHEAPSIZE]; _size = 0; }

  int size() const {
      return _size;
  }

  bool empty() const {
      return (size() == 0);
  }

  void insert(const T&);
  T extractMax();
  T peekMax() const;
  void printHeapArray() const;
  void printTree() const;
  void changeKey(const T& from, const T& to);
  void deleteItem(const T&);

  ~Heap() { delete[] _heap; };

private:
  //Helper functions
  void swap(T& a, T& b) {
      T temp = a;
      a = b;
      b = temp;
  }

  void bubbleUp(int i) {
      while (i > 0 && _heap[PARENT(i)] < _heap[i]) {
          swap(_heap[i], _heap[PARENT(i)]);
          i = PARENT(i);
      }
  }

  void bubbleDown(int i) {
      while (true) {
          int left = LEFT(i);
          int right = RIGHT(i);
          int largest = i;

          if (left < _size && _heap[left] > _heap[largest]) {
              largest = left;
          } 
          if (right < _size && _heap[right] > _heap[largest]) {
              largest = right;
          }
          

          if (largest != i) {
              swap(_heap[i], _heap[largest]);
              i = largest;
          }
          else {
              break;
          }
      }
  }

  int findIndex(const T& x) const {
      for (int i = 0; i < _size; i += 1) {
          if (_heap[i] == x) {
              return i;
          }
      }
      return -1;
  }

};

template <class T>
void Heap<T>::insert(const T& item) {
    if (_size >= DEFAULTHEAPSIZE) {
        throw std::runtime_error("Heap capacity exceeded");
    }
    _heap[_size] = item;
    bubbleUp(_size);
    _size += 1;
}

template <class T>
T Heap<T>::extractMax() {
    if (empty()) {
        throw std::out_of_range("Heap is empty");
    }
    T maxVal = _heap[0];
    _heap[0] = _heap[_size - 1];
    _size -= 1;
    bubbleDown(0);
    return maxVal;
}

template <class T>
T Heap<T>::peekMax() const {
    // TODO: What happens if the heap is empty?
    if (empty()) {
        throw std::out_of_range("Heap is empty");
    }
    return _heap[0];
};

template <class T>
void Heap<T>::printHeapArray() const {
  for (int i = 0; i < size(); i++) {
    cout << _heap[i] << " ";
  }
  cout << endl;
}

template <class T>
void Heap<T>::changeKey(const T& from, const T& to) {
    // TODO: implement this
    int index = findIndex(from);
    if (index == -1) {
        return;
    }
    _heap[index] = to;
    if (to > from) {
        bubbleUp(index);
    }
    else {
        bubbleDown(index);
    }
}

template <class T>
void Heap<T>::deleteItem(const T& x) {
    // TODO: implement this
    int index = Heap<T>::findIndex(x);
    if (index == -1) {
        return;
    }
    _heap[index] = _heap[_size - 1];
    _size -= 1;
    if (index < _size) {
        bubbleDown(index);
        bubbleUp(index);
    }
}

template <class T>
void Heap<T>::printTree() const {
  int parity = 0;
  if (size() == 0) return;
  int space = pow(2, 1 + (int)log2f(size())), i;
  int nLevel = (int)log2f(size()) + 1;
  int index = 0, endIndex;
  int tempIndex;

  for (int l = 0; l < nLevel; l++) {
    index = 1;
    parity = 0;
    for (i = 0; i < l; i++) index *= 2;
    endIndex = index * 2 - 1;
    index--;
    tempIndex = index;
    while (index < size() && index < endIndex) {
      for (i = 0; i < space - 1; i++) cout << " ";
      if (index == 0)
        cout << "|";
      else if (parity)
        cout << "\\";
      else
        cout << "/";
      parity = !parity;
      for (i = 0; i < space; i++) cout << " ";
      index++;
    }
    cout << endl;
    index = tempIndex;
    while (index < size() && index < endIndex) {
      for (i = 0; i < (space - 1 - ((int)log10(_heap[index]))); i++)
        cout << " ";
      cout << _heap[index];
      for (i = 0; i < space; i++) cout << " ";
      index++;
    }

    cout << endl;
    space /= 2;
  }
}

#endif
