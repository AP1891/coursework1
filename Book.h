#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Date.h"

class Book { // Declaring the Book class
public:
  int bookID;
  std::string bookName;
  int pageCount;
  std::string authorFirstName;
  std::string authorLastName;
  std::string bookType;
  Date dueDate;
  int borrowerID;

  // Constructor
  Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName, const std::string& type);
  void borrowBook(int memberID);
  void returnBook();
  bool isBorrowed() const;
  void displayBook() const;
  int getBorrowerID() const;
};

#endif
