#include "Book.h"
#include <iostream>
#include <ctime> // Used to get the Date
#include <iomanip> // Used to format and display the Date

// Constructor initializes Book object with default values
Book::Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName, const std::string& type)
  : bookID(id), bookName(name), authorFirstName(firstName), authorLastName(lastName), bookType(type), borrowerID(-1) {
  dueDate = Date(); // Initialize the dueDate with a default value
}

void Book::borrowBook(int memberID) {
  borrowerID = memberID; // Mark the book as borrowed and set the due date

  // Set due date to 3 days from today
  std::time_t now = std::time(0);
  std::tm* today = std::localtime(&now);
  dueDate = Date(today->tm_mday + 3, today->tm_mon + 1, today->tm_year + 1900);
}

void Book::returnBook() { // Mark the book as returned
  borrowerID = -1;  // Reset borrower ID
}

bool Book::isBorrowed() const { // Check if the book is currently borrowed
  return borrowerID != -1;
}

void Book::displayBook() const { // Display book information, including due date if the book is borrowed
  std::cout << "Book ID: " << bookID << std::endl;
  std::cout << "Book Name: " << bookName << std::endl;
  std::cout << "Page Count: " << pageCount << std::endl;
  std::cout << "Author: " << authorFirstName << " " << authorLastName << std::endl;
  std::cout << "Type: " << bookType << std::endl;
  std::cout << "Due Date: ";
  if (isBorrowed()) {
    dueDate.printDate();
  } else {
    std::cout << "Not borrowed";
  }
  std::cout << std::endl << std::endl;
}

int Book::getBorrowerID() const { // Get the ID of the member who borrowed the book
  return borrowerID;
}
