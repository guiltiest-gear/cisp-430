template <class T>
class LessThan {
 public:
  bool operator()(T a, T b) { return a < b; }
};
