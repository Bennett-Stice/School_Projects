DEBUG = -g
OPTS = $(DEBUG) -Wall -ansi -pedantic -std=c++20
CC = g++ -c $(OPTS)
LN = g++

OBJS = main.o ActivationRecord.o Function.o FunctionTable.o Program.o\
	Stack.o Statement.o Variable.o

p2: $(OBJS)
	$(LN) -o p2 $(OBJS)

main.o: main.cpp Function.hpp Program.hpp Stack.hpp Statement.hpp
	$(CC) main.cpp

ActivationRecord.o: ActivationRecord.cpp ActivationRecord.hpp Variable.hpp
	$(CC) ActivationRecord.cpp

Function.o: Function.cpp Function.hpp Stack.hpp Statement.hpp
	$(CC) Function.cpp

FunctionTable.o: FunctionTable.cpp FunctionTable.hpp Function.hpp Stack.hpp\
	Statement.hpp
	$(CC) FunctionTable.cpp

Program.o: Program.cpp Program.hpp Statement.hpp
	$(CC) Program.cpp

Stack.o: Stack.cpp Stack.hpp ActivationRecord.hpp Variable.hpp
	$(CC) Stack.cpp

Statement.o: Statement.cpp Statement.hpp ActivationRecord.hpp Function.hpp\
	FunctionTable.hpp Stack.hpp
	$(CC) Statement.cpp

Variable.o: Variable.cpp Variable.hpp
	$(CC) Variable.cpp


clean:
	/bin/rm -f p2 $(OBJS) *~
