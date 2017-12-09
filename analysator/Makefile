CC=g++
CF=-Wall -Wextra -std=c++11 -pedantic

all: main

analyser.o: analyser.cpp analyser.hpp
	$(CC) $(CF) -c analyser.cpp -o analyser.o

main.o: main.cpp analyser.hpp
	$(CC) $(CF) -c main.cpp -o main.o

main: analyser.o main.o
	$(CC) $(CF) analyser.o main.o -o main

clean:
	rm -f *.o main
