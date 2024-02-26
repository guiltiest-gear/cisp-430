// GIVEN
template <class T>
class SortBy {
 private:
  bool sortByTitle;

 public:
  SortBy(bool yes) { sortByTitle = yes; }
  bool operator()(T a, T b) {
    if (sortByTitle)
      return a <= b;
    else
      return a < b;
  }
};
