#include <iostream>
#include <memory>
#include <vector>

#include "ChartPoscpp.h"
#include "LessThanEqualcpp.h"
#include "LessThancpp.h"

template <class T>
class VectorADT {
 private:
  T** dataArray = nullptr;  // dataArray = new T*[SIZE];
  int count;
  int SIZE = 2;

 public:
  // default constructor
  VectorADT();
  // copy constructor
  VectorADT(const VectorADT& other);
  // destructor
  ~VectorADT();

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
  int insert(T* v, int pos);

  // deletes the item at index position =pos
  // if database is empty or pos is negative or an unacceptable number throws
  // exception and exits returns the number of adjustments done to shift data
  // left
  int remove(int pos);

  void topTen();
  // prints top 10 items
  // kept sorted according to position - use function objects - selection sort

  // selection sorts using chart positon
  int sort(LessThan<T> f);
  // selection sorts using title
  int sortTitle(LessThanEqual<T> f);
  // overloaded binary search that has additional parameters,this is recursive
  // binary search
  int binarySearchByTitle(int& steps, T* v, int first, int last);
  // binary search that calls the overloaded function with first =0 and last =
  // count-1; The data v contains the title being searched
  int binarySearchByTitle(int& steps, T* v);
  // radix sort - see Zybooks for algorithm, also watch the given video resource
  int radixSort(ChartPos<T> c);

  // recursive merge sort - see Zybooks for algorithm, also watch the given
  // video resource
  int mergeSortByTitle(LessThanEqual<T> le);
  void Merge(LessThanEqual<T> le, int& steps, int i, int j, int k);
  void mergeSortByTitle(LessThanEqual<T> le, int& steps, int i, int k);
};
