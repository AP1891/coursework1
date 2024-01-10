#include "Librarian.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

void readBooksFromCSV(std::vector<Book>& library, const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
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

  while (file >> bookID >> comma >> std::ws) {
    // Read the bookName field
    if (file.peek() == '"') {
      file.ignore();  // Ignore the opening quote
      getline(file, bookName, '"');  // Read until closing quote
      file.ignore();  // Ignore the comma after the closing quote
    } else {
      getline(file, bookName, ',');  // Read until the comma
    }

    // Read the rest of the fields
    file >> pageCount >> comma >> std::ws;
    getline(file, authorFirstName, ',');
    getline(file, authorLastName, ',');
    getline(file, bookType, '\n');

    library.emplace_back(bookID, bookName, authorFirstName, authorLastName, bookType);
    library.back().pageCount = pageCount;  // Set page count
  }

  file.close();
}

Librarian::Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary)
  : staffID(staffID), librarianName(name), librarianAddress(address), librarianEmail(email), librarianSalary(salary) {
}


void Librarian::addMember(const std::string& name, const std::string& address, const std::string& email) {
  int newMemberID = members.size() + 1;  // Assuming member IDs start from 1
  members.emplace_back(newMemberID, name, address, email);
  std::cout << "New member added:" << std::endl;
  std::cout << "ID: " << newMemberID << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Address: " << address << std::endl;
  std::cout << "Email: " << email << std::endl << std::endl;
}

void Librarian::issueBook(int memberID, int bookID) {
  if (memberID < 1 || memberID > members.size()) {
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }

  if (bookID < 1 || bookID > library.size()) {
    std::cout << "Invalid book ID. Please enter a valid book ID." << std::endl << std::endl;
    return;
  }


  Member& member = members[memberID - 1];

  Book& book = library[bookID - 1];

  if (book.isBorrowed()) {
    std::cout << "Book is already borrowed. Please select another book." << std::endl << std::endl;
    return;
  }

  book.borrowBook(memberID);
  member.borrowBook(&book);

  std::cout << "Book issued successfully:" << std::endl;
  std::cout << "Member ID: " << memberID << std::endl;
  std::cout << "Book ID: " << bookID << std::endl;
  std::cout << "Due Date: ";
  book.dueDate.printDate();
  std::cout << std::endl << std::endl;
}

void Librarian::returnBook(int memberID, int bookID) {

  if (memberID < 1 || memberID > members.size()) {
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }

  if (bookID < 1 || bookID > library.size()) {
    std::cout << "Invalid book ID. Please enter a valid book ID." << std::endl << std::endl;
    return;
    }

  Member& member = members[memberID - 1];
  Book& book = library[bookID - 1];

  if (!book.isBorrowed() || book.borrowerID != memberID) {
    std::cout << "This book was not borrowed by the specified member." << std::endl << std::endl;
    return;

  }

  book.returnBook();
  member.returnBook(&book);

  std::cout << "Book returned successfully:" << std::endl;
  std::cout << "Member ID: " << memberID << std::endl;
  std::cout << "Book ID: " << bookID << std::endl << std::endl;
}

void Librarian::displayBorrowedBooks(int memberID) const {
  if (memberID < 1 || memberID > members.size()) {
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }

  const Member& member = members[memberID - 1];
  member.displayBorrowedBooks();
}

void Librarian::calculateFine(int memberID) const {

  if (memberID < 1 || memberID > members.size()) {
    std::cout << "Invalid member ID. Please enter a valid member ID." << std::endl << std::endl;
    return;
  }

  const Member& member = members[memberID - 1];
  int fine = 0;

  for (const auto& book : member.booksBorrowed) {
    // Check if the book is overdue
    std::time_t now = std::time(0);
    std::tm* today = std::localtime(&now);
    Date currentDate(today->tm_mday, today->tm_mon + 1, today->tm_year + 1900);


    if (currentDate.day > book->dueDate.day || currentDate.month > book->dueDate.month || currentDate.year > book->dueDate.year) {
     // Calculate days overdue
      int daysOverdue = currentDate.day - book->dueDate.day +
	(currentDate.month - book->dueDate.month) * 30 +
	(currentDate.year - book->dueDate.year) * 365;
      fine += daysOverdue;
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

