#include <string>
class Song {
 private:
  std::string title;
  std::string singer;
  int chartPosition;

 public:
  Song();
  Song(std::string title, std::string singer, int chartPosition);
  Song(const Song& other);
  std::string toString();
  std::string getTitle() const;
  void setChartPosition(int pos);
  friend std::ostream& operator<<(std::ostream&, Song* s);
  int getChartPosition() const;
  std::string getSinger() const;
  bool operator<(Song b);   // used for search compare chartpositions
  bool operator<=(Song b);  // used for linear search compare titles
  bool operator==(Song b);
  bool operator>(Song b);
};
