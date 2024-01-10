#include "Member.h"
#include <algorithm>
#include <iostream>

Member::Member(int id, const std::string& n, const std::string& addr, const std::string& mail)
  : memberID(id), name(n), address(addr), email(mail) {}

void Member::borrowBook(Book* book) {
  booksBorrowed.push_back(book);
}

void Member::returnBook(Book* book) {
  auto it = std::find(booksBorrowed.begin(), booksBorrowed.end(), book);
  if (it != booksBorrowed.end()) {
    booksBorrowed.erase(it);
  }
}

void Member::displayBorrowedBooks() const {
  std::cout << "Books borrowed by " << name << " (ID: " << memberID << "):" << std::endl;
  if (booksBorrowed.empty()) {
    std::cout << "No books borrowed." << std::endl;
  } else {
    for (const auto& book : booksBorrowed) {
      book->displayBook();
    }
  }
  std::cout << std::endl;
}

int Member::getMemberID() const {
  return memberID;
}

const std::vector<Book*>& Member::getBooksBorrowed() const {
  return booksBorrowed;
}

void Member::setBooksBorrowed(Book* book) {
  booksBorrowed.push_back(book);
}

std::string Member::getName() const {
  return name;
}
