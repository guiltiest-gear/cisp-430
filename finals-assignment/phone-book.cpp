#include "phone-book.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>

using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::printf;
using std::set;
using std::string;
using std::tolower;
using std::transform;

char get_menu_input() {
  // Loop forever until we have valid input
  for (;;) {
    // Use a string to store the input, because you can never count on a user to
    // input anything safely, especially in any sort of C language
    string input;
    cout << "What would you like to do?\n";
    cout << "D: Display all contacts\n";
    cout << "A: Add a contact\n";
    cout << "R: Remove a contact\n";
    cout << "C: Change contact information\n";
    cout << "U: Update existing contact database\n";
    cout << "Q: Quit the application\n";
    cout << "Your choice? ";
    // Read from input, make sure it's actually input, not just a blank input
    if (getline(cin, input)) {
      if (input == "") {
        // Print an error and try again if we get a blank input
        cout << "Error! No input detected! Maybe try again?\n";
        continue;
      }
      // Otherwise, we can return our input
      return input.at(0);
    }
  }
}

void get_contacts(const char* filename, phone_book_db* database) {
  try {
    ifstream contact_file(filename);
    // Abort if we can't open the file for some reason
    if (!contact_file.is_open())
      throw "Error! Unable to open file! Aborting...";
    // Have variables to hold the name, phone numbers, and current line
    string name, phone_number, line;
    while (getline(contact_file, line)) {
      istringstream instream(line);
      // Get the name and store it
      getline(instream, name, ' ');
      // Get the phone number and store it too
      getline(instream, phone_number, '\n');
      // Construct a pair
      pair<string, string> contact(name, phone_number);
      // Insert the contact into the set
      database->insert(contact);
    }
  } catch (const char* err) {
    cout << err << '\n';
    exit(1);
  }
}

void print_contacts(const phone_book_db& database) {
  for (auto i : database) printf("%s %s\n", i.first.c_str(), i.second.c_str());
}

void add_contact(phone_book_db* database) {
  // Compile a list of names before proceeding
  set<string> name_db;
  for (auto i : *database) {
    // Copy the name of the contact
    string name = i.first;
    // Transform name strings to lowercase
    transform(name.begin(), name.end(), name.begin(),
              [](unsigned char c) { return tolower(c); });
    // Now add the modified string to the set
    name_db.insert(name);
  }

  // Do a similar dealie for input validation with the get_menu_input function
  string new_name, new_phone_number;
  for (;;) {
    cout << "What is the name of this person to add? ";
    if (getline(cin, new_name)) {
      if (new_name == "") {
        cout << "Error! No input detected! Maybe try again?\n";
        continue;
      }
      // Now check if the name exists in the database already
      auto pos = name_db.find(new_name);
      if (pos != name_db.end()) {
        cout << "Error! Name already exists in database, try again please!\n";
        continue;
      }
    }
    // If we got here, that must mean we have a unique name
    break;
  }

  // Now do the same thing for the phone number
  for (;;) {
    cout << "What is their phone number? ";
    if (getline(cin, new_phone_number)) {
      if (new_phone_number == "") {
        cout << "Error! No input detected! Maybe try again?\n";
        continue;
      }
    }
    break;
  }

  // Now that we have everything we need, we can finally construct and insert a
  // pair
  pair<string, string> new_entry(new_name, new_phone_number);
  database->insert(new_entry);
}

void remove_contact(phone_book_db* database) {
  // Figure out who we're trying to remove
  string name, phone_number;
  for (;;) {
    cout << "What is the name of this person to remove? ";
    if (getline(cin, name)) {
      if (name == "") {
        cout << "Error! No input detected! Maybe try again?\n";
        continue;
      }
    }
    break;
  }

  // Now do the same thing for the phone number
  for (;;) {
    cout << "What is their phone number? ";
    if (getline(cin, phone_number)) {
      if (phone_number == "") {
        cout << "Error! No input detected! Maybe try again?\n";
        continue;
      }
    }
    break;
  }
  // Construct a pair for searching
  pair<string, string> to_delete(name, phone_number);
  auto removal_pos = database->find(to_delete);
  if (removal_pos != database->end()) {
    database->erase(removal_pos);
    return;
  }
  cout << "Error! No matches found!\n";
}

void change_contact(phone_book_db* database) {
  // This is essentially just removing a contact, and then adding a new one
  // Keep things DRY by using existing functions
  remove_contact(database);
  add_contact(database);
}
