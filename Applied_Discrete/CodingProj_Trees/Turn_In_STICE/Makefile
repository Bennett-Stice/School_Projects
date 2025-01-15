CC = g++ -g -c -Wall -ansi -pedantic -std=c++20
LN = g++

OBJ = main.o BinaryTree.o TreeNode.o

treefun: $(OBJ)
	$(LN) -o treefun $(OBJ)

main.o: main.cpp BinaryTree.hpp TreeNode.hpp
	$(CC) main.cpp

BinaryTree.o: BinaryTree.cpp BinaryTree.hpp TreeNode.hpp
	$(CC) BinaryTree.cpp

TreeNode.o: TreeNode.cpp TreeNode.hpp
	$(CC) TreeNode.cpp

clean:
	/bin/rm -f $(OBJ) *~ treefun

