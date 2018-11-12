#Makefile

lib: library.o space.o main.o
        g++ -o lib library.o space.o main.o
main.o: main.cpp
        g++ -c main.cpp
library.o: Library.cpp
        g++ -c Library.cpp
space.o: Member.cpp
        g++ -c Space.cpp
clean:
        rm *.o lib

