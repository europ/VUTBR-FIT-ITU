CC=g++
CF=-Wall -Wextra -std=c++11 -pedantic -g

all: main

analyser.o: analyser.cpp analyser.hpp
	$(CC) $(CFLAGS) -c analyser.cpp -o analyser.o

main.o: main.cpp analyser.hpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

main: analyser.o main.o
	$(CC) $(CFLAGS) analyser.o main.o -o main

clean:
	rm -f *.o main
