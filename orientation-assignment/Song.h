#include <string>
class Song {
 private:
  std::string title;
  std::string singer;
  int chartPosition;

 public:
  // default constructor
  Song();
  // custom constructor
  Song(std::string title, std::string singer, int chartPosition);
  // convert object to string
  std::string toString();
  // operator overloading for ostream operator
  friend std::ostream &operator<<(std::ostream &, Song *s);
  // operator overloading for less than operator
  bool operator<(Song *b);
  // getter for chart position
  int getChartPosition();
  // return title
  std::string getTitle();
  // Return singer
  std::string getSinger();
  // Set title
  void setTitle(std::string title);
  // Set chart position
  void setChartPosition(int chartPosition);
  // Set singer
  void setSinger(std::string singer);
};
