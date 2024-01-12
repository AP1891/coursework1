#include "Member.h"
#include <algorithm>
#include <iostream>

// Constructor for the Member class
Member::Member(int id, const std::string& n, const std::string& addr, const std::string& mail)
  : memberID(id), name(n), address(addr), email(mail) {}

// Function to borrow a book
void Member::borrowBook(Book* book) {
  booksBorrowed.push_back(book); // the pointer to the book is added to the booksBorrowed vector to track which books are borrowed
}

void Member::returnBook(Book* book) { // Function to return a book
  auto it = std::find(booksBorrowed.begin(), booksBorrowed.end(), book); // Search the vector fully for the specified pointer of that book
  if (it != booksBorrowed.end()) { // If the book is found ("it" is not equal to booksBorrowed.end())
    booksBorrowed.erase(it); // Removes the pointer set when the book was borrowed
  }
}

void Member::displayBorrowedBooks() const { // Function to show the books borrowed by a member
  std::cout << "Books borrowed by " << name << " (ID: " << memberID << "):" << std::endl;
  if (booksBorrowed.empty()) { // If the booksBorrowed vector is empty 
    std::cout << "No books borrowed." << std::endl; // Then this says there are no borrowed books
  } else {
    for (const auto& book : booksBorrowed) { // Iterate through each pointer if the vector is not empty
      book->displayBook(); // Carry out the displayBook function for each book
    }
  }
  std::cout << std::endl;
}

int Member::getMemberID() const { // Function to return the member ID
  return memberID;
}

const std::vector<Book*>& Member::getBooksBorrowed() const { // Function to return the vector of borrowed books
  return booksBorrowed;
}

void Member::setBooksBorrowed(Book* book) { // Function to set the vector of borrowed books using push back
  booksBorrowed.push_back(book);
}

std::string Member::getName() const { // Function to return the member's name
  return name;
}
