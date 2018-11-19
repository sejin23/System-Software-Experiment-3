#Makefile

lib: Library.o Space.o Member.o Resource.o main.o
	g++ -o lib Library.o Space.o Member.o Resource.o main.o
main.o: main.cpp
	g++ -c main.cpp
Library.o: Library.cpp
	g++ -c Library.cpp
Space.o: Space.cpp
	g++ -c Space.cpp
Member.o: Member.cpp
	g++ -c Member.cpp
Resource.o: Resource.cpp
	g++ -c Resource.cpp
clean:
	rm *.o lib
