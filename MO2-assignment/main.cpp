#include <fstream>
#include <iostream>
#include <sstream>

#include "Songcpp.h"
#include "VectorADTcpp.h"

using std::string, std::ifstream, std::istringstream, std::getline, std::stoi,
    std::cout;

// adjust all the chart positions starting with index
// these could be out of order since a song could have been insert at index
// position with a chart position that is out of place assign the correct chart
// position to this song and adjust the rest by adding 1

// GIVEN
void adjustInsert(VectorADT<Song> &mySongs, int index) {
  for (int i = index; i < mySongs.size(); i++) {
    // temp stores the address of mySong element
    Song *tmp = mySongs.get(i);
    // changing chartPosition in temp changes it in the song.
    tmp->setChartPosition(i + 1);
  }
}

// adjust all the chart positions starting with index
// these could be out of order since a song could have been deleted at index
// position by subtracting one from previous chart position
void adjustRemove(VectorADT<Song> &mySongs, int index) {
  // Loop through the array and adjust chart positions accordingly
  for (int i = index; i < mySongs.size(); i++) {
    Song *tmp = mySongs.get(i);
    tmp->setChartPosition(i - 1);
  }
}

int populatedataBase(VectorADT<Song> &mySongs) {
  // ifstream input("SongsData.txt");
  // ifstream input("SongsData2.txt");
  ifstream input("SongsDataDouble.txt");
  string line, title, singer, cp;
  int chartPosition = 0, dataCount = 0;
  if (!input) {
    throw string("File Open Error ");
    exit(1);
  }
  while (getline(input, line)) {
    // std::getline(input,line);
    istringstream instream(line);
    getline(instream, title, ',');
    getline(instream, singer, ',');
    getline(instream, cp, '\n');
    // cout<<cp<<std::endl;
    chartPosition = stoi(cp);
    Song *s = new Song(title, singer, chartPosition);
    mySongs.push_back(s);
    dataCount++;
  }
  return dataCount;
}

int main() {
  VectorADT<Song> database;

  int dataCount = populatedataBase(database);
  // database.printVectorADT();
  LessThan<Song> f;
  // sort according to chart position
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

  Song *insertThis2 = new Song("fifth place", "BTS", 5);
  // insert a new song with chart position 5 at index 6 of the database
  // this will move the rest of the songs down, but not change their chart
  // position
  int insertSteps =
      database.insert(insertThis2, 5);  // will go into 6th position
  cout << "inserted song at index 6 " << insertThis2->toString()
       << " Number of insert adjust steps = " << insertSteps << '\n';
  // adjustInsert adjusts all the chartpositions at and after index 5 that were
  // out of order due to the insert
  adjustInsert(database, 5);
  // database.printVectorADT();

  cout << "After insert, size of Data base " << database.size() << '\n';
  Song *removeThis = database.get(4);
  // removes the song at index 4
  cout << "Going to Remove song " << removeThis->toString() << " at index 4\n";
  // this will move the rest of the songs up, but not change their chart
  // position
  int removeSteps = database.remove(4);
  cout << "removed element at index 4 - Number of remove adjust steps = "
       << removeSteps << '\n';
  cout << "After remove, size of Data base " << database.size() << '\n';
  database.printVectorADT();
  // adjust remove adjusts all the chart positions that were out of order
  adjustRemove(database, 4);
  database.printVectorADT();
  int searchSteps = 0;

  // back up the database
  VectorADT<Song> backup = database;
  // backup.printVectorADT();

  // use a functor that compares titles to sort by title
  LessThanEqual<Song> g;
  // use selection sort to sort backup by title
  backup.sortTitle(g);
  backup.printVectorADT();
  cout << "Searching for removed song by title " << removeThis->toString()
       << '\n';

  int found = backup.binarySearchByTitle(searchSteps, removeThis);

  if (found >= 0)
    cout << "FOUND - Took Binary Search Steps - " << searchSteps << '\n';
  else
    cout << "NOT FOUND - Took Binary Search Steps - " << searchSteps << '\n';
  cout << "*************************************\n";
  searchSteps = 0;
  found = backup.linearSearchByTitle(searchSteps, removeThis);
  if (found >= 0)
    cout << "FOUND - Took Linear Search Steps - " << searchSteps << '\n';
  else
    cout << "NOT FOUND - Took Linear Search Steps - " << searchSteps << '\n';

  searchSteps =
      0;  // reset search steps for the new search // **please add this line
          // this can be done in the binary search method too
  found = backup.binarySearchByTitle(searchSteps, insertThis2);
  if (found >= 0)
    cout << "FOUND - Took Binary Search Steps - " << searchSteps << '\n';
  else
    cout << "NOT FOUND - Took Binary Search Steps - " << searchSteps << '\n';
  cout << "*************************************\n";
  // search for the last song of the database
  Song *lastSong = database.pop();
  searchSteps = 0;
  // reset search steps for the new search // **please add this line
  // this can be done in the binary search method too
  found = backup.binarySearchByTitle(searchSteps, insertThis2);
  if (found >= 0)
    cout << "FOUND last song of database - Took Binary Search Steps - "
         << searchSteps << "\n";
  else
    cout << "NOT FOUND - Took Binary Search Steps - " << searchSteps << "\n";
  cout << "*************************************\n";
  return 0;
}
