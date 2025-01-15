AWFUL: main.o DnC.o
	g++ -g -o $@ $^

main.o: main.cpp DnC.hpp PointPair.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

DnC.o: DnC.cpp DnC.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

clean:
	/bin/rm -f *.o sort
