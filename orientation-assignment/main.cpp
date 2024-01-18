#include <fstream>
#include <iostream>
#include <sstream>

#include "Song.h"

using std::string, std::ifstream, std::istringstream, std::cout, std::cin;

// max size of the dynamic array
const int SIZE = 300;
// selection sort to sort according to chart position
int sortSongs(Song **, int size);

// print the top ten songs in the sorted array
void printTopTen(Song **, int size);
// print all the songs in the array
void print(Song **, int size);

// returns the actual number of songs read
//  if more songs than size, then they are ignored.

int populateArray(std::string filename, Song **);
// search by title
int searchASong(Song **dataArray, int size);
// get the song by chart position
Song getSong(Song **dataArray, int size, int chartPosition);

int main() {
  // create a dynamic array of pointers to Song objects
  Song **dataArray = new Song *[SIZE];
  // populate the array by reading data from the file
  int size = populateArray("SongsData.txt", dataArray);
  // int size = populateArray("SongsDataDouble.txt", dataArray);
  // print the data Array
  // print(dataArray,size);
  //  sort the song array using selection sort
  int sortSteps = sortSongs(dataArray, size);
  // print the number of steps
  cout << "****************************************\n";
  cout << "The number of steps for selection sort = " << sortSteps << '\n';
  cout << "****************************************\n";
  // print the sorted data Array
  print(dataArray, size);
  // print the top ten songs
  cout << "Printing ***************** TOP TEN *****************\n";
  printTopTen(dataArray, size);
  // search for a song by title
  int searchSteps = searchASong(dataArray, size);
  if (searchSteps == -1) {
    cout << "Error! Song not found!\n";
    // HACK: I know I really shouldn't use goto statements, but I do need to
    // deallocate everything if this happens and this is the best way I could
    // think to do it using the DRY principle
    goto cleanup;
  }
  // Print the song found
  cout << "Song found: " << dataArray[searchSteps] << '\n';
  // print the number of steps
  cout << "****************************************\n";
  // Adjust result by 1 to account for first step in the search
  cout << "The number of steps for linear search = " << searchSteps + 1 << '\n';
  cout << "****************************************\n";

cleanup:
  // Deallocate and nullify the elements in the array
  for (int i = 0; i < size; i++) {
    delete dataArray[i];
    dataArray[i] = nullptr;
  }
  // Deallocate the array itself
  delete[] dataArray;
  // Nullify the pointer to avoid out of bounds errors
  dataArray = nullptr;

  return 0;
}
// Requires non negative size
// Effects Sorts the Songs dataArray
// using selection sortSongs
// Modifies dataArray
int sortSongs(Song **dataArray, int size) {
  // GIVEN CODE
  int steps = 0, minIndex = 0;
  Song *minValue;
  for (int i = 0; i < size; i++) {
    minValue = dataArray[i];
    minIndex = i;
    for (int j = i + 1; j < size; j++) {
      steps++;
      if (*dataArray[j] < minValue) {
        minValue = dataArray[j];
        minIndex = j;
      }
    }
    dataArray[minIndex] = dataArray[i];
    dataArray[i] = minValue;
  }
  return steps;
}

// Requires valid filename to open file
// Effects fills the Songs dataArray
//
// Modifies dataArray
int populateArray(std::string filename, Song **dataArray) {
  // GIVEN CODE
  int size = 0, chartPosition;
  string line, title, singer;

  try {
    ifstream input(filename);
    // If we couldn't open the file, throw an error
    if (input.fail()) throw string(filename + " File Open Error");
    while (!input.eof()) {
      getline(input, line);
      istringstream inpline(line);
      std::getline(inpline, title, ',');
      std::getline(inpline, singer, ',');
      inpline >> chartPosition;
      dataArray[size] = new Song(title, singer, chartPosition);
      size++;
    }
  } catch (string error) {
    cout << error << '\n';
  }
  return size;
}
// R size >0
// E uses the overloaded << operator in Song to print all the Songs
// M nothing
void print(Song **dataArray, int size) {
  // Loop over the array in entirety
  for (int i = 0; i < size; i++)
    // Overloaded operator automatically converts to string
    cout << dataArray[i] << '\n';
}
// Requires size >0
// Effects Prints top ten songs by calling print data method
//  if there are less than 10 songs in array then it prints them all otherwise
//  it prints first 10 songs
// Modifies nothing
void printTopTen(Song **dataArray, int size) {
  // Check if size is less than 10
  if (size < 10) {
    // If so, then just print what we have
    for (int i = 0; i < size; i++) cout << dataArray[i] << '\n';
    // Otherwise, only loop 10 times
  } else {
    for (int i = 0; i < 10; i++) cout << dataArray[i] << '\n';
  }
}

// Requires size >0
// Effects Linear Searches for the song based on title
// Prompts user for title
// Modifies Nothing
int searchASong(Song **dataArray, int size) {
  string title;
  cout << "Which title are you searching? ";
  getline(cin, title);
  // Now that we have our title, loop over the array until we get our match
  for (int i = 0; i < size; i++)
    // Make sure we don't accidentally go out of bounds
    if (getSong(dataArray, size, i).getTitle() == title) return i;

  // If we got here, we didn't find anything
  return -1;
}

// Requires size >=0
//  Effect Searches for song by title using chart position returns index if
//  found otherwise -1
// uses linear search
// Modifies nothing

Song getSong(Song **dataArray, int size, int chartPosition) {
  // GIVEN CODE
  if (chartPosition < size)
    return *dataArray[chartPosition];
  else
    throw string("Exception - Array Out of Bounds");
}
