#ifndef DATE_H
#define DATE_H

// Declaring the Date class
class Date {
public:
  int day;
  int month;
  int year;

  // Constructors
  Date();
  Date(int d, int m, int y);
  void printDate() const;
};

#endif
