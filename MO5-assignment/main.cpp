#include <fstream>
#include <iostream>
#include <sstream>

#include "LinkedListcpp.h"
#include "Songcpp.h"

using std::cout, std::string, std::ifstream, std::istringstream, std::getline,
    std::stoi;

void testDummyData();
int populateDatabase(LinkedList<Song> &database, SortBy<Song> f);
void testDatabase(LinkedList<Song> &database, SortBy<Song> f);

// GIVEN
int main() {
  // test the dummy database
  testDummyData();
  // create the song database
  LinkedList<Song> database;
  // select sort by title so  create the function object with true parameter
  SortBy<Song> f(true);
  // populate the database and report the steps/complexity
  int steps = populateDatabase(database, f);
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "Populated the Song Data Base \n";
  cout << "Number of steps needed for insert is " << steps << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  // database.printList();
  // put the database through its paces.
  testDatabase(database, f);
  return 0;
}

// GIVEN
int populateDatabase(LinkedList<Song> &database, SortBy<Song> f) {
  int steps = 0, insertSteps = 0, chartPosition = 0, dataCount = 0;
  // ifstream input("SongsData.txt");
  ifstream input("SongsDataDouble.txt");
  string line, title, singer, cp;
  Song s;
  if (!input) {
    throw string("File Open Error");
    exit(1);
  }
  while (getline(input, line)) {
    // std::getline(input,line);
    string token;
    istringstream instream(line);
    getline(instream, title, ',');
    getline(instream, singer, ',');
    getline(instream, cp, '\n');
    // std::cout<<cp<<std::endl;
    chartPosition = stoi(cp);
    s.setTitle(title);
    s.setSinger(singer);
    s.setChartPosition(chartPosition);
    insertSteps = database.insert(s, f);
    // std::cout<<"INSERT STEPS = "<<insertSteps<<"\n";
    steps += insertSteps;
  }
  return steps;
}

// GIVEN
void testDatabase(LinkedList<Song> &database, SortBy<Song> f) {
  Song newSong("candle in the wind", "Purple", 500);
  Song found;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "INSERTING SONG " << newSong.toString() << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  database.insert(newSong, f);
  // database.printList();
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "SEARCH THIS INSERTED SONG " << newSong.toString() << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  found = database.get(newSong);

  cout << "\n results " << found.toString() << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "SEARCH SONG at INDEX 3 \n ";
  found = database.get(3);

  cout << "\n results " << found.toString() << "\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "REMOVING THIS SONG IN THE MIDDLE OF THE DATABASE \n ";
  database.remove(found);
  cout << "SEARCH THIS REMOVED SONG " << found.toString() << '\n';
  found = database.get(found);
  cout << " \n results " << found.toString() << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "SEARCH SONG at INDEX 0 \n ";
  found = database.get(0);
  cout << " \n results " << found.toString() << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "REMOVING THE FIRST SONG OF THE DATABASE \n ";
  database.remove(found);
  cout << "SEARCH THIS REMOVED SONG \n ";
  found = database.get(found);
  cout << "\n results " << found.toString() << '\n';
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  database.printList();
}

// GIVEN
void testDummyData() {
  Song one("One ", "Apple", 1);
  Song two("Two ", "Boy", 2);
  Song three("Three", "Cat", 3);
  Song four("Four ", "Dog", 4);
  LinkedList<Song> songList;
  SortBy<Song> f(false);
  songList.insert(two, f);
  songList.insert(four, f);

  songList.insert(one, f);
  songList.insert(three, f);
  songList.printList();
  cout << "**********************\n";
  cout << "REMOVING from the Start - ONE \n";
  songList.remove(one);
  songList.printList();
  cout << "**********************\n";
  Song result = songList.get(one);
  if (result.getTitle() == "") cout << one.getTitle() << " Not Found\n";
  cout << "ADDING BACK ONE  \n";
  songList.add(one);
  songList.printList();
  cout << "**********************\n";
  cout << "SEARCHING for Song at Index 2  \n";
  result = songList.get(2);
  cout << result.getTitle() << "\nFound at index position 2 \n";
  cout << "REMOVING from the MIDDLE - THREE \n";
  songList.remove(three);
  songList.printList();
  cout << "**********************\n";
  cout << "REMOVING from the end - FOUR \n";
  songList.remove(four);
  songList.printList();
  cout << "**********************\n";
  cout << "Empty the database -REMOVING  ONE \n";
  songList.remove(one);
  songList.printList();
  cout << "**********************\n";
  cout << "Empty the database -REMOVING  TWO \n";
  songList.remove(two);
  songList.printList();
  cout << "**********************\n";
  cout << "ADDING BACK THREE - to test insert does place in  order  \n";
  songList.insert(three, f);
  songList.printList();
  cout << "**********************\n";
  cout << "ADDING BACK FOUR - to test insert does place in  order  \n";
  songList.add(four);
  songList.printList();
}
