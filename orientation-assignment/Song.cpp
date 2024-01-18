#include "Song.h"

#include <ostream>
#include <string>

using std::string, std::to_string, std::ostream;

// default constructor
Song::Song() {
  title = "";
  singer = "";
  chartPosition = 0;
}

// custom constructor
Song::Song(string title, string singer, int chartPosition) {
  // Populate class instance with arguments
  this->title = title;
  this->singer = singer;
  this->chartPosition = chartPosition;
}

// Convert object to string
string Song::toString() {
  return "Title: " + title + " Singer: " + singer +
         " ChartPosition: " + to_string(chartPosition);
}

ostream &operator<<(ostream &str, Song *s) {
  str << s->toString();
  return str;
}

// Getters
int Song::getChartPosition() { return chartPosition; }
string Song::getTitle() { return title; }
string Song::getSinger() { return singer; }

// Setters
void Song::setTitle(string title) { this->title = title; }
void Song::setChartPosition(int chartPosition) {
  this->chartPosition = chartPosition;
}
void Song::setSinger(string singer) { this->singer = singer; }

// operator < overloading
// Return true if the song's chart position is less than the other's
bool Song::operator<(Song *b) {
  return this->chartPosition < b->getChartPosition();
}
