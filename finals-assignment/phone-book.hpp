#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H

#include <set>
#include <string>
#include <utility>

// Use typedef to make my life easier
typedef std::set<std::pair<std::string, std::string>> phone_book_db;

// Get the input from the user
// Requires: Nothing
// Effects: Gets user input for the menu
// Modifies: Nothing
char get_menu_input();

// Read and store contacts from a file
// Requires: Filename and database
// Effects: Writes new contacts to database
// Modifies: The database
void get_contacts(const char* filename, phone_book_db* database);

// Print the contacts currently in the database
// Requires: Database
// Effects: Prints the contents of the database to standard output
// Modifies: Nothing
void print_contacts(const phone_book_db& database);

// Add a contact to the database
// Requires: Database
// Effects: Adds a contact to the database
// Modifies: Database
void add_contact(phone_book_db* database);

// Change a contact in the database
// Requires: Database
// Effects: Replaces a contact to the database
// Modifies: Database
void change_contact(phone_book_db* database);

// Find and remove a contact in the database
// Requires: Database
// Effects: Removes an entry in the database
// Modifies: Database
void remove_contact(phone_book_db* database);

#endif  // !PHONE_BOOK_H
