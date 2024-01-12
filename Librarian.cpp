#include "Librarian.h"
#include <iostream>
#include <fstream> // Used to read from the CSV file
#include <sstream> // Used to delare and use strings
#include <ctime> // Used to handle the date function

void readBooksFromCSV(std::vector<Book>& library, const std::string& filename) { // Declaration of the function with the constant reference to the filename string
  std::ifstream file(filename); // this function populates the library vector with the Books that are read from the file given

  if (!file.is_open()) { // If the file doesn't open then display an error message and exit the program
    std::cout << "Error opening file: " << filename << std::endl;
    exit(1);
  }

  // Skip the header line
  std::string header;
  getline(file, header);

  int bookID;
  int pageCount;
  std::string bookName;
  std::string authorFirstName;
  std::string authorLastName;
  std::string bookType;
  char comma;
  
  while (file >> bookID >> comma >> std::ws) { // Keep reading each line from the file read the bookID and a comma, std::ws is used to skip spaces
    // Read the bookName field
    if (file.peek() == '"') { // If the book name has quotes read until the end quote
      file.ignore();  // Ignore the opening quote
      getline(file, bookName, '"');  // Read until closing quote
      file.ignore();  // Ignore the comma after the closing quote
    } else {
      getline(file, bookName, ',');  // Otherwise read until the comma 
    }

    // Read the rest of the fields
    file >> pageCount >> comma >> std::ws;
    getline(file, authorFirstName, ',');
    getline(file, authorLastName, ',');
    getline(file, bookType, '\n');

    library.emplace_back(bookID, bookName, authorFirstName, authorLastName, bookType);
    // For each book read, a new Book is created and added to the library vector using emplace_back
    library.back().pageCount = pageCount;  // Set page count
  }

  file.close();
}

// Constructor for the Librarian class
Librarian::Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary)
  : staffID(staffID), librarianName(name), librarianAddress(address), librarianEmail(email), librarianSalary(salary) {
}

// Function to add a member to the program
void Librarian::addMember(const std::string& name, const std::string& address, const std::string& email) {
  int newMemberID = members.size() + 1;  // Assuming member IDs start from 1
  members.emplace_back(newMemberID, name, address, email); // Add the member to the members vector
  std::cout << "New member added:" << std::endl;
  std::cout << "ID: " << newMemberID << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Address: " << address << std::endl;
  std::cout << "Email: " << email << std::endl << std::endl;
}


void Librarian::issueBook(int memberID, int bookID) { // Function to issue a book to a member
  if (memberID < 1 || memberID > members.size()) { // Validate member ID to make sure member has been created and that the memberID is greater than the member vector
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }

  if (bookID < 1 || bookID > library.size()) { // Check the book ID
    std::cout << "Invalid book ID. Please enter a valid book ID." << std::endl << std::endl;
    return;
  }

  // Get the member and book objects - 1 from both as they both start from 1
  Member& member = members[memberID - 1];
  Book& book = library[bookID - 1];

  if (book.isBorrowed()) { // Check if the book is already borrowed
    std::cout << "Book is already borrowed. Please select another book." << std::endl << std::endl;
    return;
  }
  
  // Borrow the book and update member's borrowed Books
  book.borrowBook(memberID);
  member.borrowBook(&book);

  // Display the successfully issued message with the member ID and the Due date for the borrowed book
  std::cout << "Book issued successfully:" << std::endl;
  std::cout << "Member ID: " << memberID << std::endl;
  std::cout << "Book ID: " << bookID << std::endl;
  std::cout << "Due Date: ";
  book.dueDate.printDate();
  std::cout << std::endl << std::endl;
}

void Librarian::returnBook(int memberID, int bookID) {
  // Check member ID
  if (memberID < 1 || memberID > members.size()) {
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }
  // Check book ID
  if (bookID < 1 || bookID > library.size()) {
    std::cout << "Invalid book ID. Please enter a valid book ID." << std::endl << std::endl;
    return;
    }
  
  // Get the member and book objects
  Member& member = members[memberID - 1];
  Book& book = library[bookID - 1];
  
  if (!book.isBorrowed() || book.borrowerID != memberID) { // Check if the book is borrowed by the specified member
    std::cout << "This book was not borrowed by the specified member." << std::endl << std::endl;
    return;

  }
  // Return the book and update member's borrowed Books
  book.returnBook();
  member.returnBook(&book);

  std::cout << "Book returned successfully:" << std::endl;
  std::cout << "Member ID: " << memberID << std::endl;
  std::cout << "Book ID: " << bookID << std::endl << std::endl;
}

void Librarian::displayBorrowedBooks(int memberID) const {
  if (memberID < 1 || memberID > members.size()) { // Check the member ID
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }
  
  // Get member and display borrowed books
  const Member& member = members[memberID - 1];
  member.displayBorrowedBooks();
}

void Librarian::calculateFine(int memberID) const {

  if (memberID < 1 || memberID > members.size()) { // Check the member ID
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }

  // Get the member and calculate fine for overdue books
  const Member& member = members[memberID - 1];
  int fine = 0;

  for (const auto& book : member.booksBorrowed) {
    // Check if the book is overdue
    std::time_t now = std::time(0);
    std::tm* today = std::localtime(&now);
    Date currentDate(today->tm_mday, today->tm_mon + 1, today->tm_year + 1900);

    // Compare the current date with the due date of the book
    if (currentDate.day > book->dueDate.day || currentDate.month > book->dueDate.month || currentDate.year > book->dueDate.year) {
     // Calculate days overdue
      int daysOverdue = currentDate.day - book->dueDate.day +
	(currentDate.month - book->dueDate.month) * 30 +
	(currentDate.year - book->dueDate.year) * 365;
      fine += daysOverdue; // Add up the fine based on the number of days overdue
    }
  }
  std::cout << "Fine for Member ID " << memberID << ": £" << fine << std::endl << std::endl;
}

int Librarian::getStaffID() const {
  return staffID;
}

void Librarian::setStaffID(int staffID) {
  this->staffID = staffID;
}

int Librarian::getSalary() const {
  return librarianSalary;
}

void Librarian::setSalary(int salary) {
  librarianSalary = salary;
}

