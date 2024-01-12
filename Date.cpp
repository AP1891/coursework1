#include "Date.h"
#include <iostream>
#include <iomanip> // Used to format the Date


Date::Date() : day(0), month(0), year(0) {} // Default constructor for the Date class

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {} // Intitalise variables for the Date class

void Date::printDate() const { // This function prints the date in the format DD/MM/YYYY
  std::cout << std::setfill('0') << std::setw(2) << day << '/'
	    << std::setw(2) << month << '/' << year;
}
