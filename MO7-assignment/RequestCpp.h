#include "Request.h"

Request::Request() {
  action = "";
  title = "";
  singer = "";
  chartPosition = -1;
}

Request::Request(std::string action, std::string title, std::string singer,
                 int chartPosition) {
  this->title = title;
  this->singer = singer;
  this->action = action;
  this->chartPosition = chartPosition;
}
std::string Request::toString() {
  return "Action: " + action + " Title: " + title + " Singer: " + singer +
         " ChartPosition: " + std::to_string(chartPosition);
}

std::string Request::getTitle() { return title; }
std::string Request::getSinger() { return singer; }
std::string Request::getAction() { return action; }
int Request::getChartPosition() { return chartPosition; }

// compares titles and returns true if titles are same using string compare
// method
bool Request::operator==(Request other) {
  return title.compare(other.getTitle()) == 0;
}
