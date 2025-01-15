sort: proj1.o Sorter.o
	g++ -g -o $@ $^

proj1.o: proj1.cpp Sorter.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

Sorter.o: Sorter.cpp Sorter.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

clean:
	/bin/rm -f *.o sort
