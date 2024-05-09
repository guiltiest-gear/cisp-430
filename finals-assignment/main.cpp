#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#include "phone-book.hpp"

using std::cout;
using std::string;
using std::tolower;

int main() {
  // Create a database that will contain our values
  phone_book_db database;
  // Read from contacts.txt and write to database
  get_contacts("contacts.txt", &database);
  for (;;) {
    switch (tolower(get_menu_input())) {
      // If we didn't get a good option
      default:
        cout << "Error! Invalid option, please try again!\n";
        break;
      // Exit the application
      case 'q':
        exit(0);
      // Print out the contacts
      case 'd':
        print_contacts(database);
        break;
      // Update the contacts database
      case 'u':
        get_contacts("updates.txt", &database);
        break;
      // Add a contact
      case 'a':
        add_contact(&database);
        break;
      // Remove a contact
      case 'r':
        remove_contact(&database);
        break;
      // Change a contact
      case 'c':
        change_contact(&database);
        break;
    }
  }
  return 0;
}
