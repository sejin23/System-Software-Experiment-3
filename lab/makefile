#Makefile

lib: Library.o Member.o Resource.o main.o
	g++ -o lib Library.o Member.o Resource.o main.o
main.o: main.cpp
	g++ -c main.cpp
library.o: Library.cpp
	g++ -c Library.cpp
Member.o: Member.cpp
	g++ -c Member.cpp
Resource.o: Resource.cpp
	g++ -c Resource.cpp
clean:
	rm *.o lib
