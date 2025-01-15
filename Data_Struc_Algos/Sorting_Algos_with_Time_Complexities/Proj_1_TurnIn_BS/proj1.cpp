#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <string>

#include "Sorter.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    //make a list from the file
    list<string> loadIn;
    ifstream ifile;

    ifile.open(argv[1]);

    int size;
    ifile >>size;

    for (int i=0;i<size;i++)
    {
        string next;
        ifile>>next;
        loadIn.push_back(next);
    }

    //pick the sorting system and sort it accordingly
    string sortSystem=argv[2];

    //make the sorted list
    list<string> sortedList;


    if (sortSystem=="bubble")
    {
        sortedList=bubbleSort(loadIn);
    }

    if (sortSystem=="merge")
    {
        sortedList=mergeSort(loadIn);
    }

    if (sortSystem=="quick")
    {
        sortedList=quickSort(loadIn);
    }

    if (sortSystem=="heap")
    {
        sortedList=heapSort(loadIn);
    }

    if (sortSystem=="sys")
    {
        sortedList=sysSort(loadIn);
    }

    //handle if it needs to be printed
    if (argc==4 && string (argv[3]) == "-print")
    {
        for (string val:sortedList)
        {
            cout<<val<<" ";
        }
    }

    return 0;
}
