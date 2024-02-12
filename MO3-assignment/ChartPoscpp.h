template <class T>
class ChartPos {
 public:
  int operator()(T a) { return a.getChartPosition(); }
};
