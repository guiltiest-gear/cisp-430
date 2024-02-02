#include "Song.h"

Song::Song() {
  title = "";
  singer = "";
  chartPosition = 0;
}

Song::Song(std::string title, std::string singer, int chartPosition) {
  this->title = title;
  this->singer = singer;
  this->chartPosition = chartPosition;
}

std::string Song::toString() {
  return "Title: " + title + " Singer: " + singer +
         " ChartPosition: " + std::to_string(chartPosition);
}

// testing copy constructor for Song since it may be needed by copy constructor
// of vector ADT

Song::Song(const Song &other) {
  title = other.getTitle();
  singer = other.getSinger();
  chartPosition = other.getChartPosition();
}

std::ostream &operator<<(std::ostream &str, Song *s) {
  str << s->toString();
  return str;
}

int Song::getChartPosition() const { return chartPosition; }
void Song::setChartPosition(int pos) { chartPosition = pos; }
bool Song::operator<(Song b) { return chartPosition < b.getChartPosition(); }
bool Song::operator<=(Song b) { return title.compare(b.getTitle()) <= 0; }
bool Song::operator>(Song b) { return title.compare(b.getTitle()) > 0; }

bool Song::operator==(Song b) { return title.compare(b.getTitle()) == 0; }
std::string Song::getTitle() const { return title; }
std::string Song::getSinger() const { return singer; }
