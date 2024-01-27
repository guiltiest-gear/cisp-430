#include <fstream>
#include <iostream>
#include <sstream>

#include "Songcpp.h"
#include "VectorADTcpp.h"

// This file is completed.

using std::cout, std::getline, std::ifstream, std::string, std::istringstream,
    std::stoi;

int populatedataBase(VectorADT<Song> *mySongs) {
  ifstream input("SongsDataDouble.txt");
  string line, title, singer, cp;  // chart position in string
  int chartPosition = 0, dataCount = 0;
  if (!input) {
    throw string("File Open Error\n");
    exit(1);
  }
  while (getline(input, line)) {
    istringstream instream(line);
    getline(instream, title, ',');
    getline(instream, singer, ',');
    getline(instream, cp, '\n');
    chartPosition = stoi(cp);
    // FIX: Apparently this causes a memory leak, despite the clean up at the
    // end, figure out why
    Song *s = new Song(title, singer, chartPosition);
    mySongs->push_back(s);
    dataCount++;
  }
  return dataCount;
}

int main() {
  VectorADT<Song> database;

  int dataCount = populatedataBase(&database);
  // database.printVectorADT();
  LessThan<Song> f;
  int steps = database.sort(f);
  cout << "*************************************\n";
  cout << "Selection Sorting By Chart Position Steps = " << steps << '\n';
  cout << "*************************************\n";
  database.printVectorADT();
  Song *insertThis = new Song("music is this", "BTS", dataCount + 1);
  database.push_back(insertThis);
  cout << "*************************************\n";
  cout << "After push_back, size of Data base " << database.size() << '\n';

  // database.printVectorADT();
  Song *temp = database.pop();
  cout << "The last song is " << temp->toString() << '\n';
  temp = database.pop_back();
  cout << "After pop_back, size of Data base " << database.size() << '\n';
  // database.printVectorADT();

  Song *insertThis2 = new Song("fifth place", "BTS", 5);  // chartposition
  int insertSteps =
      database.insert(insertThis2, 5);  // will go into 6th position
  cout << "inserted song at index 6 " << insertThis2->toString()
       << " Number of insert adjust steps= " << insertSteps << '\n';
  // database.printVectorADT();
  cout << "After insert, size of Data base " << database.size() << '\n';
  Song *removeSong = database.get(4);
  cout << "Going to Remove song fifth place at index 4 " << '\n';
  int removeSteps = database.remove(4);
  cout << "removed element at index 4 - Number of remove adjust steps= "
       << removeSteps << '\n';
  cout << "After remove, size of Data base " << database.size() << '\n';
  int searchSteps = 0;
  cout << "Searching for song by title " << removeSong->toString() << "\n";

  int found = database.searchByTitle(searchSteps, removeSong);
  if (found >= 0)
    cout << "FOUND - Took Linear Search Steps - " << searchSteps << "\n";
  else
    cout << "NOT FOUND - Took Linear Search Steps - " << searchSteps << "\n";
  cout << "*************************************\n";
  return 0;
}
