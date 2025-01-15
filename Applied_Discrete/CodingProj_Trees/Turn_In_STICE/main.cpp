#include <iostream>

#include "BinaryTree.hpp"
#include "TreeNode.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    BinaryTree myTree;

    const string origTree[12]={"D","i","s","c","r","e","t","e","=","f","u","n"};


    for (int i=0; i<12; i++)
    {
        myTree.insert(origTree[i]);
    }

    cout << myTree;

    cout << "Enter a character to add: ";
    string addMe;
    cin >> addMe;

    while (addMe!="quit")
    {
        myTree.insert(addMe);
        cout << myTree << endl << endl;

        cout << "Enter a character to add: ";
        cin >> addMe;
    }

    return 0;
}
