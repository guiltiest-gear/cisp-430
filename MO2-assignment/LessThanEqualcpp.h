template <class T>
class LessThanEqual {
 public:
  bool operator()(T a, T b) { return a <= b; }
};
