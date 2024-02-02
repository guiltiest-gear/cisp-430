#include <cstdlib>
#include <iostream>
#include <string>

#include "VectorADT.h"

template <class T>
VectorADT<T>::VectorADT() {
  dataArray = new T*[SIZE];
  count = 0;
}

// GIVEN Copy constructor that is called when a new vectorADT ic created and
// equated with the "other" ADT vector object
template <class T>
VectorADT<T>::VectorADT(const VectorADT<T>& other) {
  dataArray = new T*[SIZE];
  count = 0;

  for (int i = 0; i < other.size(); i++) {
    T* temp = other.get(i);
    T* s = new T();
    *s = *temp;  // created a copy constructor in Song to make this work
    push_back(s);
  }
}

// destructor
template <class T>
VectorADT<T>::~VectorADT() {
  for (int i = 0; i < count; i++) {
    // Delete and nullify elements
    delete dataArray[i];
    dataArray[i] = nullptr;
  }
  // Delete and nullify the array itself
  delete[] dataArray;
  dataArray = nullptr;
}

template <class T>
void VectorADT<T>::resizeADT() {
  size_t newSize = 2 * count;
  SIZE *= 2;
  T** tempADT = new T*[newSize];
  for (int i = 0; i < count; i++) tempADT[i] = dataArray[i];
  delete[] dataArray;
  dataArray = tempADT;
}

template <class T>
void VectorADT<T>::push_back(T* v) {
  if (count >= SIZE) resizeADT();
  dataArray[count] = v;
  count++;
}

template <class T>
T* VectorADT<T>::pop() {
  if (empty()) {
    throw std::string("No such element exception");
    exit(1);
  }
  return dataArray[count - 1];
}

template <class T>
T* VectorADT<T>::pop_back() {
  if (empty()) {
    throw std::string("No such element exception");
    exit(1);
  }
  T* v = new T();
  v = dataArray[count - 1];
  count--;
  return v;
}

template <class T>
void VectorADT<T>::printVectorADT() {
  for (int i = 0; i < count; i++) std::cout << dataArray[i] << '\n';
}

template <class T>
int VectorADT<T>::size() const {
  return count;
}

template <class T>
int VectorADT<T>::sortTitle(LessThanEqual<T> less) {
  int steps = 0;
  T* minValue = new T();
  int minIndex = 0;
  for (int i = 0; i < count; i++) {
    minValue = dataArray[i];
    minIndex = i;
    for (int j = i + 1; j < count; j++) {
      if (less(*dataArray[j], *minValue)) {
        minValue = dataArray[j];
        minIndex = j;
      }
      steps++;
    }
    dataArray[minIndex] = dataArray[i];
    dataArray[i] = minValue;
  }
  return steps;
}

template <class T>
int VectorADT<T>::sort(LessThan<T> less) {
  int steps = 0;
  T* minValue = new T();
  int minIndex = 0;
  for (int i = 0; i < count; i++) {
    minValue = dataArray[i];
    minIndex = i;
    for (int j = i + 1; j < count; j++) {
      if (less(*dataArray[j], *minValue)) {
        minValue = dataArray[j];
        minIndex = j;
      }
      steps++;
    }
    dataArray[minIndex] = dataArray[i];
    dataArray[i] = minValue;
  }
  return steps;
}

template <class T>
bool VectorADT<T>::empty() {
  return (count <= 0);
}

template <class T>
T* VectorADT<T>::get(int i) const {
  if (i < 0 && i >= count) {
    throw std::string("No such element exception");
    exit(1);
  }
  return dataArray[i];
}

template <class T>
void VectorADT<T>::set(int i, T* t) {
  if (i < 0 && i >= count) {
    throw std::string("No such element exception");
    exit(1);
  }
  dataArray[i] = t;
}

template <class T>
int VectorADT<T>::insert(T* v, int pos) {
  int adjustSteps = 0;
  if (pos < 0) {
    throw std::string("No such position exception");
    exit(1);
  }

  if (pos >= count) {
    push_back(v);
    adjustSteps++;
  }

  if (pos < count) {
    push_back(dataArray[count - 1]);
    adjustSteps++;
    for (int i = count - 2; i > pos; i--) {
      dataArray[i] = dataArray[i - 1];
      adjustSteps++;
    }
    dataArray[pos] = v;
  }
  return adjustSteps;
}

template <class T>
int VectorADT<T>::remove(int pos) {
  int adjustSteps = 0;
  if (count == 1) {
    dataArray = nullptr;
    adjustSteps++;
  } else {
    for (int i = pos; i < count - 1; i++) {
      dataArray[i] = dataArray[i + 1];
      adjustSteps++;
    }

    dataArray[count - 1] = nullptr;
  }
  count--;
  return adjustSteps;
}

template <class T>
int VectorADT<T>::binarySearchByTitle(int& steps, T* v, int first, int last) {
  while (first <= last) {
    int middle = (first + last) / 2;
    steps++;
    if (*dataArray[middle] == *v)
      return middle;
    else if (*dataArray[middle] > *v)
      last = middle - 1;
    else
      first = middle + 1;
  }
  // If we got here, then that means it wasn't present
  return -1;
}

// GIVEN
template <class T>
int VectorADT<T>::binarySearchByTitle(int& steps, T* v) {
  steps = 0;
  return binarySearchByTitle(steps, v, 0, count - 1);
}

template <class T>
int VectorADT<T>::linearSearchByTitle(int& steps, T* v) {
  for (int i = 0; i < count; i++) {
    if (v == dataArray[i]) return i;
    steps++;
  }
  return -1;
}
