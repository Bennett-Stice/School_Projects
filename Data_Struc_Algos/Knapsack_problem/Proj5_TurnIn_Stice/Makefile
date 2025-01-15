burn: main.o TWITS.o
	g++ -g -o $@ $^

main.o: main.cpp TWITS.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

TWITS.o: TWITS.cpp TWITS.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

clean:
	/bin/rm -f *.o sort
