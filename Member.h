#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "Book.h"

// Declaring the Member class
class Member {
public:
  int memberID;
  std::string name;
  std::string address;
  std::string email;
  std::vector<Book*> booksBorrowed;

  // Constructor
  Member(int id, const std::string& n, const std::string& addr, const std::string& mail);
  void borrowBook(Book* book);
  void returnBook(Book* book);
  void displayBorrowedBooks() const;
  int getMemberID() const;
  const std::vector<Book*>& getBooksBorrowed() const;
  void setBooksBorrowed(Book* book);
  std::string getName() const;
};

#endif
