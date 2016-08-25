CC = g++
CWIN = i686-w64-mingw32-g++
CFLAGS = -Wall -std=c++11
CFILES = main.cpp engine.cpp game.cpp entity.cpp

all:
	$(CC) $(CFLAGS) -o main $(CFILES) `sdl2-config --cflags --libs`


win:
	$(CWIN) $(CFLAGS) -o main $(CFILES) `sdl2-config --cflags --libs`

clean:
	rm *.o main
