#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

#include "Song.h"
#include "VectorADT.h"

// GIVEN
template <class T>
VectorADT<T>::VectorADT() {
  dataArray = new T*[SIZE];
  count = 0;
}

// double the size of the dataArray
// create a temporary dataArray of double the size

// copy over the current data Array and then delete it
// use REM documentation
template <class T>
void VectorADT<T>::resizeADT() {
  // NOTE here is where the integer SIZE will get doubled
  // Double the size variable
  int newsize = SIZE * 2;
  // Create a new array with the new size
  T** tmp = new T*[newsize];

  // Delete dataArray
  for (int i = 0; i < SIZE; i++)
    // Copy over all the elements from the first array into the new one
    tmp[i] = dataArray[i];

  delete[] dataArray;
  // Overwrite dataArray with tmp
  dataArray = tmp;
  SIZE = newsize;
}

// appends an element to the end of the VectorADT
// increments count by 1
// if run out of SIZE, resize the vector
// REM documentation
template <class T>
void VectorADT<T>::push_back(T* v) {
  // Increment count
  count++;
  // Check if we have enough room first, if not, call resizeADT
  if (count > SIZE) resizeADT();

  // Put the value into the correct place
  dataArray[count - 1] = v;
}

// returns a copy of the element from the end of the VectorADT
// does not delete any element
// no resize of the vector
// REM documentation
template <class T>
T* VectorADT<T>::pop() {
  // Use an if else statement to make sure that the array has an item
  // if it does, return the item in the array. If not, exit.
  if (dataArray[count - 1] == nullptr) {
    exit(1);
  } else {
    return dataArray[count - 1];
  }
}

// removes an element from the end of the VectorADT
// decrements size by 1
// no resize of the vector
// REM documentation
template <class T>
T* VectorADT<T>::pop_back() {
  // This function does exactly what pop() does but it will
  // also remove the item from the end of the VectorADT

  // Just call pop to adhere to DRY principle
  T* value = pop();
  delete value;
  value = nullptr;
  // Decrement count as well
  count--;
  return value;
}

// GIVEN
template <class T>
void VectorADT<T>::printVectorADT() {
  for (int i = 0; i < count; i++) std::cout << dataArray[i] << "\n";
}

// GIVEN
template <class T>
int VectorADT<T>::size() const {
  return count;
}

// FILL IN THE BLANK FOR COMPARISON
template <class T>
int VectorADT<T>::sort(LessThan<T> less) {
  int steps = 0;
  T* minValue;
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

// GIVEN
template <class T>
bool VectorADT<T>::empty() {
  return (count <= 0);
}

// GIVEN
template <class T>
T* VectorADT<T>::get(int i) const {
  if (i >= 0 && i < count) {
    return dataArray[i];
  } else {
    throw std::string("No such element exception");
    exit(1);
  }
}

// GIVEN
template <class T>
void VectorADT<T>::set(int i, T* t) {
  if (i >= 0 && i < count) {
    dataArray[i] = t;
  } else {
    throw std::string("No such element exception");
    exit(1);
  }
}

// USE template
// inserts the object at the given INDEX position NOT chart position
// Does NOT adjust chart position
// THROWS exception if index out of bounds
// right adjusts the elements to the right of the inserted object
// returns number of adjusted steps
template <class T>
int VectorADT<T>::insert(T* v, int pos) {
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

// USE template
// removes the object at the given INDEX position NOT chart position
// Does NOT adjust chart position
// THROWS exception if index out of bounds
// left adjusts the elements to the right of the inserted object
// returns number of adjusted steps
template <class T>
int VectorADT<T>::remove(int pos) {
  int adjustSteps = 0;
  // Check if database is empty or an out of bounds access first
  if (pos < 0 && pos >= count) {
    throw std::string("No such element exception");
    exit(1);
  }

  // Now shift everything into the correct position
  for (int i = pos; i < count; i++) {
    // Copy the element after the pos index into the index at pos
    dataArray[i] = dataArray[i + 1];
    // Increment adjustSteps
    adjustSteps++;
  }

  // Use a pointer to delete
  T* tmp = dataArray[count - 1];
  // Perform the delete, nullification, decrement
  delete tmp;
  tmp = nullptr;
  count--;

  return adjustSteps;
}

// Linear search
// use the overloaded == operator of the Song objects
// returns -1 if not found else returns the found index
template <class T>
int VectorADT<T>::searchByTitle(int& steps, T* v) {
  // Class contains count variable, use that for the for loop
  for (int i = 0; i < count; i++) {
    // Just your standard linear search, nothing to really see
    if (v == dataArray[i]) return i;
    // Increment steps every time we don't find it
    steps++;
  }
  return -1;
}

// Print the top ten songs
template <class T>
void VectorADT<T>::topTen() {
  // Loop and print
  for (int i = 0; i < 10; i++) std::cout << dataArray[i] << '\n';
}
