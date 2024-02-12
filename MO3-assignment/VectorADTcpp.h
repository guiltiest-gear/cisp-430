#include <iostream>
#include <string>
#include <vector>

#include "VectorADT.h"

template <class T>
VectorADT<T>::VectorADT() {
  dataArray = new T *[SIZE];
  count = 0;
}

// Copy constructor
template <class T>
VectorADT<T>::VectorADT(const VectorADT<T> &other) {
  this->count = other.count;
  this->SIZE = other.SIZE;
  this->dataArray = new T *[count];
  for (int i = 0; i < other.size(); i++) {
    T *tmp = other.get(i);
    T *s = new T();
    *s = *tmp;
    // HACK: For some reason, the count variable gets the wrong value calling
    // push_back, so this is the next best thing
    this->dataArray[i] = other.get(i);
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
  // Delete and nullify array
  delete[] dataArray;
  dataArray = nullptr;
}

template <class T>
void VectorADT<T>::resizeADT() {
  int newSize = 2 * count;
  SIZE *= 2;
  T **tempADT = new T *[newSize];
  for (int i = 0; i < count; i++) tempADT[i] = dataArray[i];
  delete[] dataArray;
  dataArray = tempADT;
}

template <class T>
void VectorADT<T>::push_back(T *v) {
  if (count >= SIZE) resizeADT();
  dataArray[count] = v;
  count++;
}

template <class T>
T *VectorADT<T>::pop() {
  if (empty()) {
    throw std::string("No such element exception");
    exit(1);
  }
  return dataArray[count - 1];
}

template <class T>
T *VectorADT<T>::pop_back() {
  if (empty()) {
    throw std::string("No such element exception");
    exit(1);
  }
  T *v = new T();
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
  T *minValue = new T();
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
  T *minValue = new T();
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
T *VectorADT<T>::get(int i) const {
  if (i < 0 && i >= count) {
    throw std::string("No such element exception");
    exit(1);
  }
  return dataArray[i];
}

template <class T>
void VectorADT<T>::set(int i, T *t) {
  if (i < 0 && i >= count) {
    throw std::string("No such element exception");
    exit(1);
  }
  dataArray[i] = t;
}

template <class T>
int VectorADT<T>::insert(T *v, int pos) {
  int adjustSteps = 0;
  // Check if database is empty or an out of bounds access first
  if (pos < 0 && pos >= count) {
    throw std::string("No such element exception");
    exit(1);
  }

  // Increase the count
  count++;
  // Allocate room for another element
  dataArray[count] = new T;
  // Now move everything over using a reverse for loop
  for (int i = count - 1; i >= pos; i--) {
    // Take the element just before i and move it to i
    dataArray[i] = dataArray[i - 1];
    // Increment adjustSteps each time
    adjustSteps++;
  }

  // Now we can actually write the value to the array
  // Just use the set function, no need to reinvent the wheel
  set(pos, v);

  return adjustSteps;
}

template <class T>
int VectorADT<T>::remove(int pos) {
  int steps = 0;
  if (pos < 0 && pos >= count) {
    throw std::string("No such element exception");
    exit(1);
  }

  for (int i = pos; i < count - 1; i++) {
    dataArray[i] = dataArray[i + 1];
    steps++;
  }

  // Perform the delete, nullification, decrement
  delete dataArray[count - 1];
  dataArray[count - 1] = nullptr;
  count--;

  return steps;
}

template <class T>
int VectorADT<T>::binarySearchByTitle(int &steps, T *v, int first, int last) {
  int middle = (first + last) / 2;
  if (first > middle) {
    return -1;
  } else if (*dataArray[middle] == *v) {
    steps++;
    return middle;
  } else if (*dataArray[middle] > *v) {
    steps++;
    last = middle - 1;
    return binarySearchByTitle(steps, v, first, last);
  } else {
    steps++;
    first = middle + 1;
    return binarySearchByTitle(steps, v, first, last);
  }
}

template <class T>
int VectorADT<T>::binarySearchByTitle(int &steps, T *v) {
  steps = 0;
  return binarySearchByTitle(steps, v, 0, count - 1);
}

template <class T>
void VectorADT<T>::Merge(LessThanEqual<T> le, int &steps, int left, int mid,
                         int right) {
  int merge_size = right - left + 1;  // Size of merge partition
  int merge_pos = 0;                  // Position to merge
  int left_pos = 0;                   // Position of left elements
  int right_pos = 0;                  // Position of right elements
  T *merge_numbers[merge_size];       // Array for merged numbers

  // Init left part
  left_pos = left;
  // Init right part
  right_pos = mid + 1;

  // Increment before we begin
  steps++;
  // Add smallest element from left or right part to merged numbers
  while (left_pos <= mid && right_pos <= right) {
    if (le(*dataArray[left_pos], *dataArray[right_pos])) {
      merge_numbers[merge_pos] = dataArray[left_pos];
      left_pos++;
    } else {
      merge_numbers[merge_pos] = dataArray[right_pos];
      right_pos++;
    }
    merge_pos++;
    steps++;
  }

  // If the left part is not empty, add the remaining elements to merged numbers
  while (left_pos <= mid) {
    merge_numbers[merge_pos] = dataArray[left_pos];
    left_pos++;
    merge_pos++;
    steps++;
  }

  // If the right part is not empter, add the remaining elements to merged
  // numbers
  while (right_pos <= right) {
    merge_numbers[merge_pos] = dataArray[right_pos];
    right_pos++;
    merge_pos++;
    steps++;
  }

  // Now copy everything back into the original array
  for (merge_pos = 0; merge_pos < merge_size; merge_pos++) {
    dataArray[left + merge_pos] = merge_numbers[merge_pos];
    steps++;
  }
}

// call merge with the functor, steps and partition indices
// Merge(le,steps, i, j, k);
template <class T>
void VectorADT<T>::mergeSortByTitle(LessThanEqual<T> le, int &steps, int left,
                                    int right) {
  int mid = 0;

  if (left < right) {
    mid = left + (right - left) / 2;  // Find the midpoint
    // Recursively sort left and right partitions
    mergeSortByTitle(le, steps, left, mid);
    mergeSortByTitle(le, steps, mid + 1, right);

    // Now merge left and right parts into sorted order
    Merge(le, steps, left, mid, right);
  }
}

template <class T>
int VectorADT<T>::mergeSortByTitle(LessThanEqual<T> le) {
  int steps = 0;
  mergeSortByTitle(le, steps, 0, size() - 1);
  return steps;
}

template <class T>
int VectorADT<T>::radixSort(ChartPos<T> c) {
  int steps = 0, max_digit = 0, digit_count = 0;

  // Figure out what's the largest digit
  max_digit = c(*dataArray[0]);
  for (int i = 1; i < count; i++)
    if (c(*dataArray[i]) > max_digit) max_digit = c(*dataArray[i]);

  // Now figure out how many places the digit has
  do {
    digit_count++;
    max_digit /= 10;
  } while (max_digit);

  // Create 10 vectors to act as buckets
  std::vector<int> *buckets = new std::vector<int>[10];

  // Start with least significant digit
  int pow10 = 1;
  for (int digit_index = 0; digit_index < digit_count; digit_index++) {
    std::vector<T *> *buckets = new std::vector<T *>[10];
    for (int i = 0; i < count; i++) {
      int bucket_index = (c(*dataArray[i]) / pow10) % 10;
      buckets[bucket_index].push_back(dataArray[i]);
    }
    int arr_index = 0;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < buckets[i].size(); j++) {
        dataArray[arr_index] = buckets[i][j];
        arr_index++;
        steps++;
      }
    }

    // Go to next significant digit
    pow10 *= 10;
    // Clean up the buckets
    delete[] buckets;
    buckets = nullptr;
  }

  // Delete the other buckets
  delete[] buckets;
  buckets = nullptr;
  return steps;
}
