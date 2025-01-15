DEBUG = -g
OPTS = $(DEBUG) -Wall -ansi -pedantic -std=c++20
LDFLAGS = -lncurses

CC=g++ $(OPTS) -c
LN=g++

OBJS = Proj_2_BS.o AirportAnimator.o

fly: $(OBJS)
	$(LN) -o fly $(OBJS) $(LDFLAGS)

Proj_2_BS.o: Proj_2_BS.cpp AirportAnimator.hpp
	$(CC) Proj_2_BS.cpp

AirportAnimator.o: AirportAnimator.cpp AirportAnimator.hpp
	$(CC) AirportAnimator.cpp

clean:
	/bin/rm -rf *~ $(OBJS) fly
