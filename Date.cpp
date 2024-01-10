#include "Date.h"
#include <iostream>
#include <iomanip>

Date::Date() : day(0), month(0), year(0) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

void Date::printDate() const {
  std::cout << std::setfill('0') << std::setw(2) << day << '/'
	    << std::setw(2) << month << '/' << year;
}
