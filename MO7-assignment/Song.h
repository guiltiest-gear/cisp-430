#include <string>

class Song {
 private:
  std::string title;
  std::string singer;
  int chartPosition;

 public:
  Song();
  Song(std::string title, std::string singer, int chartPosition);
  std::string toString();
  std::string getTitle();
  void setChartPosition(int pos);
  friend std::ostream& operator<<(std::ostream&, Song* s);
  int getChartPosition();
  bool operator<(Song b);   // used for search compare chartpositions
  bool operator<=(Song b);  // used for binary search compare titles
  bool operator==(Song b);  // used for removal
};
