#pragma once
#include <string>

#include "Song.h"

Song::Song() {
  title = "";
  singer = "";
  chartPosition = 0;
}

// GIVEN
Song::Song(std::string title, std::string singer, int chartPosition) {
  this->title = title;
  this->singer = singer;
  this->chartPosition = chartPosition;
}

// GIVEN
std::string Song::toString() {
  return "Title: " + title + " Singer: " + singer +
         " ChartPosition: " + std::to_string(chartPosition);
}
//
// GIVEN
std::ostream& operator<<(std::ostream& str, Song* s) {
  str << s->toString();
  return str;
}

// GIVEN
int Song::getChartPosition() { return chartPosition; }
// GIVEN
void Song::setChartPosition(int pos) { chartPosition = pos; }
// GIVEN
bool Song::operator<(Song b) { return chartPosition < b.getChartPosition(); }
// GIVEN
bool Song::operator<=(Song b) { return title.compare(b.getTitle()) <= 0; }

bool Song::operator==(Song b) { return title.compare(b.getTitle()) == 0; }
// GIVEN
std::string Song::getTitle() { return title; }
