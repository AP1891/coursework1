#include "Librarian.h"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) { // Check if the correct number of command-line arguments is provided
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  // Get the filename from the command-line arguments
  std::string filename = argv[1];

  // Get Librarian details from the user
  int staffID;
  std::string name, address, email;
  int salary;

  std::cout << "Enter Librarian details:" << std::endl;
  std::cout << "Staff ID: ";
  std::cin >> staffID;

  std::cout << "Name: ";
  std::cin >> name; 

  std::cout << "Address: ";
  std::cin >> address; 

  std::cout << "Email: ";
  std::cin >> email;

  std::cout << "Salary: ";
  std::cin >> salary;

  // Create a Librarian object with user-provided details
  Librarian librarian(staffID, name, address, email, salary);

  // Read books from the CSV file and populate the library
  readBooksFromCSV(librarian.library, filename);

  int choice;
  do { // Do while loop to keep the program running until the choice is 0 to end the program
    // Show the menu options to the librarian
    std::cout << "Enter the corresponding number to carry out the following options: " << std::endl;
    std::cout << "1. Add a member" << std::endl;
    std::cout << "2. Issue a book" << std::endl;
    std::cout << "3. Return a book" << std::endl;
    std::cout << "4. Display all books borrowed by a member" << std::endl;
    std::cout << "5. Calculate fine for a member" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Switch statement to handle user choices
    // Corresponding cases to carry out the corresponding functions
    switch (choice) {
    case 1: {
      std::string memberName;
      std::string memberAddress;
      std::string memberEmail;
      std::cout << "Enter member name: ";
      std::cin.ignore();
      std::getline(std::cin, memberName);
      std::cout << "Enter member address: ";
      std::getline(std::cin, memberAddress);
      std::cout << "Enter member email: ";
      std::getline(std::cin, memberEmail);
      librarian.addMember(memberName, memberAddress, memberEmail);
      break;
    }
    case 2: {
      int memberID;
      int bookID;
      std::cout << "Enter member ID: ";
      std::cin >> memberID;
      std::cout << "Enter book ID: ";
      std::cin >> bookID;
      librarian.issueBook(memberID, bookID);
      break;
    }
    case 3: {
      int memberID;
      int bookID;
      std::cout << "Enter member ID: ";
      std::cin >> memberID;
      std::cout << "Enter book ID: ";
      std::cin >> bookID;
      librarian.returnBook(memberID, bookID);
      break;
    }
    case 4: {
      int memberID;
      std::cout << "Enter member ID: ";
      std::cin >> memberID;
      librarian.displayBorrowedBooks(memberID);
      break;
    }
    case 5: {
      int memberID;
      std::cout << "Enter member ID: ";
      std::cin >> memberID;
      librarian.calculateFine(memberID);
      break;
    }
    case 0:
      // Exit the program if input is 0
      std::cout << "Exiting program. Goodbye!" << std::endl;
      break;
    default:
      // Default statement if a choice entered is not a valid choice
      std::cout << "Invalid choice. Please enter a valid option." << std::endl;
    }
  } while (choice != 0);

  return 0;
}
