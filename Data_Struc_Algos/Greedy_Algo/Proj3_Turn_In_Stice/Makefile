toxic: main.o TWJob.o
	g++ -g -o $@ $^

main.o: main.cpp TWJob.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

TWJob.o: TWJob.cpp TWJob.hpp
	g++ -g -c -Wall -ansi -pedantic -std=c++20 $<

clean:
	/bin/rm -f *.o sort
