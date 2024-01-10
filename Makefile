CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

librarian_system: Librarian.o Member.o Book.o Date.o main.o
	$(CXX) $(CXXFLAGS) -o librarian_system Librarian.o Member.o Book.o Date.o main.o

Librarian.o: Librarian.cpp Librarian.h Member.h Book.h Date.h
	$(CXX) $(CXXFLAGS) -c Librarian.cpp

Member.o: Member.cpp Member.h Book.h Date.h
	$(CXX) $(CXXFLAGS) -c Member.cpp

Book.o: Book.cpp Book.h Date.h
	$(CXX) $(CXXFLAGS) -c Book.cpp

Date.o: Date.cpp Date.h
	$(CXX) $(CXXFLAGS) -c Date.cpp

main.o: main.cpp Librarian.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm *.o
	rm librarian_system
