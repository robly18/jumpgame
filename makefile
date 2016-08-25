CC = g++
CFLAGS = -Wall -std=c++11
CFILES = main.cpp engine.cpp game.cpp entity.cpp

all:
	$(CC) $(CFLAGS) -o main $(CFILES) `sdl2-config --cflags --libs`

clean:
	rm *.o main

