#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Librarian.h"
#include "Book.h"
#include "Member.h"
#include "Date.h"

TEST_CASE("Test Librarian class") {
  Librarian librarian(1, "John", "10 Downing Street", "john@example.com", 30000);
  // Add a member for testing
  librarian.addMember("Dave", "1 Main Road", "dave@example.com");

  SECTION("Check added member") {
    REQUIRE(librarian.members.size() == 1);
    REQUIRE(librarian.members[0].getName() == "Dave");
  }

  SECTION("Issuing a valid book") {
    // Manually add a book to the library
    librarian.library.emplace_back(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction");
    // Issue the book
    librarian.issueBook(1, 1);
    REQUIRE(librarian.library[0].isBorrowed());
    REQUIRE(librarian.members[0].getBooksBorrowed().size() == 1);
}

  SECTION("Returning a valid book") {
    Book book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction");
    librarian.issueBook(1, 1);
    librarian.returnBook(1, 1);
    REQUIRE(!book.isBorrowed());
    REQUIRE(librarian.members[0].getBooksBorrowed().empty());
  }
}

TEST_CASE("Test Member class") {
  Member member(1, "Dave", "1 Main Road", "dave@example.com");
  Book book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction");

  
  SECTION("Returning a book") {
    member.borrowBook(&book);  
    member.returnBook(&book); 
    REQUIRE(member.getBooksBorrowed().empty());
    REQUIRE(!book.isBorrowed());
  }
}

TEST_CASE("Test Book class") {
  Book book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction");

  SECTION("Borrowing the book") {
    book.borrowBook(1);
    REQUIRE(book.isBorrowed());
    REQUIRE(book.getBorrowerID() == 1);
  }

  SECTION("Returning the book") {
    book.borrowBook(1);
    book.returnBook();
    REQUIRE(!book.isBorrowed());
    REQUIRE(book.getBorrowerID() == -1);
  }
}

TEST_CASE("Test Date class") {
  Date date(1, 1, 2000);

  SECTION("Printing the date") {
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());  // Redirect cout to capture output
    date.printDate();
    std::cout.rdbuf(old_cout);  
    REQUIRE(oss.str() == "01/01/2000");
  }
}

TEST_CASE("Test addMember function") {
  Librarian librarian(1, "John", "10 Downing Street", "john@example.com", 30000);

  SECTION("Adding a member") {
    librarian.addMember("Dave", "1 Main Road", "dave@example.com");
    REQUIRE(librarian.members.size() == 1);
    REQUIRE(librarian.members[0].getName() == "Dave");
  }

  SECTION("Adding multiple members") {
    librarian.addMember("Dave", "1 Main Road", "dave@example.com");
    librarian.addMember("Bob", "2 Main St", "bob@example.com");
    REQUIRE(librarian.members.size() == 2);
    REQUIRE(librarian.members[1].getName() == "Bob");
  }
}

TEST_CASE("Test issueBook function") {
  Librarian librarian(1, "John", "10 Downing Street", "john@example.com", 30000);
  librarian.addMember("Dave", "1 Main Road", "dave@example.com");

  SECTION("Issuing a valid book") {
    librarian.library.push_back(Book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction"));
    librarian.issueBook(1, 1);
    REQUIRE(librarian.library[0].isBorrowed());
    REQUIRE(librarian.members[0].getBooksBorrowed().size() == 1);
  }

  SECTION("Issuing an already borrowed book") {
    librarian.library.push_back(Book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction"));
    librarian.issueBook(1, 1);  // Borrow the book
    librarian.issueBook(1, 1);  // Try to borrow the same book again
    REQUIRE(librarian.members[0].getBooksBorrowed().size() == 1);
  }

  SECTION("Issuing a book with invalid member ID") {
    librarian.library.push_back(Book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction"));
    librarian.issueBook(0, 1);  // Invalid member ID
    REQUIRE(librarian.members[0].getBooksBorrowed().empty());
  }

  SECTION("Issuing a book with invalid book ID") {
    librarian.library.push_back(Book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction"));
    librarian.issueBook(1, 0);  // Invalid book ID
    REQUIRE(librarian.members[0].getBooksBorrowed().empty());
  }
}

TEST_CASE("Test returnBook function") {
  Librarian librarian(1, "John", "10 Downing Street", "john@example.com", 30000);
  librarian.addMember("Dave", "1 Main Road", "dave@example.com");
  librarian.library.push_back(Book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction"));

  SECTION("Returning a valid book") {
    librarian.issueBook(1, 1);
    librarian.returnBook(1, 1);
    REQUIRE(!librarian.library[0].isBorrowed());
    REQUIRE(librarian.members[0].getBooksBorrowed().empty());
  }

  SECTION("Returning an already returned book") {
    librarian.issueBook(1, 1);
    librarian.returnBook(1, 1);  // Return the book
    librarian.returnBook(1, 1);  // Try to return the same book again
    REQUIRE(librarian.members[0].getBooksBorrowed().empty());
  }
}

TEST_CASE("Test displayBorrowedBooks function") {
  Librarian librarian(1, "John", "10 Downing Street", "john@example.com", 30000);
  librarian.addMember("Dave", "1 Main Road", "dave@example.com");
  
  // Create a Book object
  Book book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction");
  
  // Manually set the pageCount for this test case
  book.pageCount = 208;

  librarian.library.push_back(book);
  librarian.issueBook(1, 1);

  SECTION("Displaying borrowed books for a valid member") {
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf()); 
    librarian.displayBorrowedBooks(1);
    std::cout.rdbuf(old_cout); 
    REQUIRE(oss.str() == "Books borrowed by Dave (ID: 1):\nBook ID: 1\nBook Name: The Great Gatsby\nPage Count: 208\nAuthor: F. Scott Fitzgerald\nType: Fiction\nDue Date: 13/01/2024\n\n\n");
  }

  SECTION("Displaying borrowed books for an invalid member") {
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());
    librarian.displayBorrowedBooks(0);  
    std::cout.rdbuf(old_cout); 
    REQUIRE(oss.str() == "Invalid member ID. Please enter a valid member ID.\n\n");
  }
}

TEST_CASE("Test calculateFine function") {
  Librarian librarian(1, "John", "10 Downing Street", "john@example.com", 30000);
  librarian.addMember("Dave", "1 Main Road", "dave@example.com");
  librarian.library.push_back(Book(1, "The Great Gatsby", "F. Scott", "Fitzgerald", "Fiction"));

  SECTION("Calculating fine for a member with overdue books") {
    librarian.issueBook(1, 1);
    librarian.library[0].dueDate = Date(1, 1, 2024);  
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());
    librarian.calculateFine(1);
    std::cout.rdbuf(old_cout);
    REQUIRE(oss.str() == "Fine for Member ID 1: £9\n\n");
  }

  SECTION("Calculating fine for a member with no overdue books") {
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());  
    librarian.calculateFine(1);
    std::cout.rdbuf(old_cout); 
    REQUIRE(oss.str() == "Fine for Member ID 1: £0\n\n");
  }

  SECTION("Calculating fine for an invalid member") {
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());  
    librarian.calculateFine(0); 
    std::cout.rdbuf(old_cout); 
    REQUIRE(oss.str() == "Invalid member ID. Please enter a valid member ID.\n\n");
  }
}
