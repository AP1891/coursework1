#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <vector>
#include "Book.h"
#include "Member.h"

class Librarian {
private:
  int staffID;
  std::string librarianName;
  std::string librarianAddress;
  std::string librarianEmail;
  int librarianSalary;

public:
  std::vector<Book> library;
  std::vector<Member> members;

  Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary);

  int getStaffID() const;
  void setStaffID(int staffID);

  int getSalary() const;
  void setSalary(int salary);

  void addMember(const std::string& name, const std::string& address, const std::string& email);
  void issueBook(int memberID, int bookID);
  void returnBook(int memberID, int bookID);
  void displayBorrowedBooks(int memberID) const;
  void calculateFine(int memberID) const;
};

void readBooksFromCSV(std::vector<Book>& library, const std::string& filename);

#endif
