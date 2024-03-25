#include <string>
class Request {
 private:
  std::string action;
  std::string title;
  std::string singer;
  int chartPosition;

 public:
  Request();
  Request(std::string action, std::string title, std::string singer,
          int chartPosition);
  std::string toString();
  std::string getTitle();
  std::string getSinger();
  std::string getAction();
  int getChartPosition();
  bool operator==(Request other);

  // complete this function operator = overloading.
  // Could be reason for segmentation fault
  // Request& operator=(const Request& other);
};
