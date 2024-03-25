#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Queuecpp.h"
#include "RequestCpp.h"
#include "Songcpp.h"

using std::cout, std::string, std::istringstream, std::ifstream;

void populateRequests(Queue<Request> &q);
void populateSongDataBase(LinkedList<Song> &list);
void processQueue(LinkedList<Song> &list, Queue<Request> &q);
void processRequest(std::string action, std::string title, std::string singer,
                    int chartPos);

// GIVEN
int main() {
  LinkedList<Song> list;
  Queue<Request> q;

  populateSongDataBase(list);  // fill the Songs Data Base into Linked List

  cout << "*************************************\n";
  list.printList();  //
  cout << "*************************************\n";
  populateRequests(q);  // fill the request q
  cout << '\n';
  cout << "---------------PRINTING QUEUE-------------------\n";
  q.printList();
  cout << "------------------------------------\n";
  processQueue(list, q);  // process the requests
  cout << "*************************************\n";
  list.printList();
  cout << "*************************************\n";
}

// GIVEN
// Requires  an empty linked list
// Effects fills the list with request by reading from the RequestData.txt
// Modifies the queue by filling it
void populateRequests(Queue<Request> &q) {
  string line, token, title, singer, action;
  int chartPos = -1;
  cout << "*************** IN POPULATE REQUEST ***************\n";
  try {
    ifstream input("RequestData.txt");
    if (input.fail()) throw string("FILE OPEN ERROR EXCEPTION\n");
    while (getline(input, line)) {
      istringstream instream(line);

      // cout<<line <<"\n";
      getline(instream, action, ',');
      getline(instream, title, ',');
      getline(instream, singer, ',');
      instream >> chartPos;
      // create a Request object
      Request r(action, title, singer, chartPos);
      // cout<<r.getAction()<<"\n";
      // add it to the queue..
      q.add(r);
    }

  } catch (string message) {
    cout << message;
    exit(1);
  }
}

// GIVEN
// Requires Filled data base , song to play
// Effects Finds song using get, if found plays it
// Modifies nothing
string playSong(LinkedList<Song> &list, Song s) {
  if (list.get(s) >= 0) {
    return "PLAYING :" + s.toString() + "\n";
  } else {
    return "SONG NOT FOUND\n";
  }
}

// GIVEN
// Requires filled database
// Effects calls print methood to print top ten songs
// Modifies nothing
void printTopTenSongs(LinkedList<Song> &list) {
  cout << "PLAYING TOP TEN SONG __________\n";
  list.print(10);
}

// Requires filled Song Database, a Song to add. The chart position given in the
// song is where it will get added. Note this is a Song that is not supposed to
// exist in database. Effects adds the song from its original chart position
// Modifies the Song database. Adjust chart position of all Songs affected by
// this addition- this adjustment is done in insert method using adjustPosition
// method. If the Process Queue adds a Song that already is in the database,
// then a duplicate entry can occur.
void addThisSong(LinkedList<Song> &list, Song s) {
  list.insert(s, s.getChartPosition());
  int found = list.get(s);
  if (found >= 0) {
    cout << "ADDED THIS SONG " << found + 1 << " ";
    list.printSong(found + 1);
  } else {
    cout << "SORRY CANNOT FIND SONG\n";
  }
}

// TODO
// Requires filled Song Database, a Song to remove
// Effects if found, removes the song from its original chart position
// Modifies the Song database. Adjust chart position of all Songs affected by
// this removal- this adjustment is done in remove method using adjustPosition
// method
void removeThisSong(LinkedList<Song> &list, Song s) {
  list.remove(s);
  int found = list.get(s);
  if (found >= 0) {
    cout << "SORRY CANNOT REMOVE THIS SONG - STILL FOUND AT " << found;
  } else {
    int chart_pos = s.getChartPosition();
    cout << "REMOVED THIS SONG\n";
    cout << "THE SONG AT CHART POSITION" << chart_pos << " IS NOW ";
    list.printSong(chart_pos);
    cout << '\n';
  }
}

// TODO
// Requires filled Song Database, a Song to move and its new position
// Effects removes the song from its original chart position and inserts into
// given position Modifies the Song database. Adjust chart position of all Songs
// affected by this insertion and removal. - this adjustment is done in remove
// method using adjustPosition method
void moveThisSong(LinkedList<Song> &list, Song s, int pos) {
  int chartPos = list.get(s);
  cout << "MOVING SONG " << s.toString() << '\n';
  list.move(s, pos);
  cout << "ITS NEW CHART POSITION\n";
  list.printSong(pos);
  cout << "THE SONG AT PREVIOUS POSITION " << chartPos + 1 << " IS NOW ";
  list.printSong(chartPos + 1);
}

// GIVEN
// Requires filled database, a single request
// Effects Processes the request
// Modifies nothing
void processRequest(LinkedList<Song> &list, string action, string title,
                    string singer, int chartPos) {
  Song s(title, singer, chartPos);
  char ch = action[0];

  switch (ch) {
    case 'P':
      cout << playSong(list, s) << "\n";
      break;
    case 'A':
      addThisSong(list, s);
      break;
    case 'R':
      removeThisSong(list, s);
      break;
    case 'M':
      moveThisSong(list, s, chartPos);
      break;
    case 'T':
      printTopTenSongs(list);
      break;
  }
}

// Requires filled database, filled Request Queue
// Effects Processes requests by implementing the action given in each request
// Modifies q, empties it after processing
void processQueue(LinkedList<Song> &list, Queue<Request> &q) {
  int request_number = 1;
  for (Queue<Request>::Iterator it = q.begin(); !(it == q.end()); ++it) {
    Request req = (*it)->getData();
    string action = req.getAction();
    string title = req.getTitle();
    string singer = req.getSinger();
    int chart_pos = req.getChartPosition();
    cout << "---------------------------------------------------------------"
            "----------\n";
    cout << "Request Number " << request_number << " " << req.toString()
         << '\n';
    processRequest(list, action, title, singer, chart_pos);
    cout << "---------------------------------------------------------------"
            "----------\n";
    request_number++;
    cout << "---------------------------------------------------------------"
            "----------\n";
  }

  while (!q.empty()) q.remove();
}

// GIVEN
// Requires the empty linked list database
// Effects if the file exists and accessible, reads from file and inserts songs
// IN SORTED ORDER ACCORDING TO CHART POSITION// Big O(N^2)  ---> Why?
// Modifies list - fills it with songs, returns sorted linked list
void populateSongDataBase(LinkedList<Song> &list) {
  string line, token, title, singer;
  int chartPos = -1;
  try {
    ifstream input("SongsData.txt");
    if (input.fail()) throw string("FILE OPEN ERROR EXCEPTION\n");
    while (getline(input, line)) {
      istringstream instream(line);
      getline(instream, title, ',');
      getline(instream, singer, ',');
      instream >> chartPos;
      Song s(title, singer, chartPos);
      list.insert(s);
    }
  } catch (string message) {
    cout << message;
  }
}
