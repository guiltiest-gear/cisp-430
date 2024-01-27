#pragma once
#include <iostream>
#include <memory>

#include "LessThancpp.h"

template <class T>

class VectorADT {
 private:
  T** dataArray = nullptr;
  int count;  // make sure count gets updated everytime you
              // add and remove songs, in functions like push_back, pop_back etc
  int SIZE = 2;  // if your computer slows down while running,
                 // you may increase this number to 20
  // This is NOT a constant, its an integer now, it gets changed in the
  // resize function

 public:
  // default constructor
  VectorADT();

  // return address of element at index position i
  T* get(int i) const;

  // set the element e at position i
  void set(int i, T*);

  // print the entire database
  void printVectorADT();

  // print the number of items specified
  void printVectorADT(int number);

  // double the size of the database by
  // creating another database twice the size and copying
  // the existing database into it. The existing one is then deleted
  void resizeADT();

  // returns true if database is empty, false otherwise
  bool empty();

  // returns the number of items in the database
  int size() const;

  // add an item to the end of the database
  void push_back(T*);

  // remove and return the last element of the database if there is one
  T* pop_back();

  // "peeks" ie returns a pointer to the last element without removing or
  // deleting it
  T* pop();

  // inserts at the proper position, no sorting necessary
  // element is inserted at index =pos
  // if pos is negative or unacceptable number throws exception and exits
  // returns the number of adjustments done to shift data to right
  // example of how to throw exception: throw new std::string("No such element
  // exception");
  int insert(T* v, int pos);

  // deletes the item at index position =pos
  // if database is empty or pos is negative or an unacceptable number throws
  // exception and exits returns the number of adjustments done to shift data
  // left
  int remove(int pos);

  // Delete all the elements within the array
  void clear();

  // prints top 10 items
  void topTen();

  // kept sorted according to position - use function objects - selection sort
  int sort(LessThan<T> f);

  // allows the user to search by title (linear search)
  int searchByTitle(int& steps, T* v);
};
