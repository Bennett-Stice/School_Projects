/**
 * @author Bennett Stice
 * @date 4/11/2024
 */


#include "TWITS.hpp"

#include <fstream>
#include <iostream>
#include <list>
using namespace std;

//create a 2-D array to fill in later
#define MAXVALUE 10000
int M[MAXVALUE][MAXVALUE];

int main (int argc, char *argv[])
{

    // pull in filename and the print option from command prompt.
    string fName = argv[1];
    string print;
    if (argc ==3)
        print = argv[2];

    // build input stream from filename
    ifstream ifile(fName);

    //set the amount of task and the deadline for them to be completed.
    int taskAmount,deadline;
    ifile>>taskAmount>>deadline;
    TWITS *tasks=new TWITS[taskAmount]; // list of all jobs

    //initialize the total penalty of all jobs
    int maxPenalty=0;

    //create a list of all the items
    list<TWITS>all_items;

    // for each job read from input file into the array of tasks, add the task's penaly to the max penalty, and add the task to all_items
    for (int i=0;i<taskAmount;i++)
    {
        ifile>>tasks[i];
        maxPenalty+=tasks[i].penalty();
        all_items.push_front(tasks[i]);
    }

    //set the top row to all zeroes
    for (int index=0; index<=deadline; index++)
        M[0][index]=0;

    //create a list of all the items you have to store
    list<TWITS>burned_items;

    //apply the knapsack algorythm
    for (int i=1;i<=taskAmount;i++)
    {
        for (int w=1;w<=deadline;w++)
        {
            if (tasks[i-1].time()>w)
                M[i][w]=M[i-1][w];
            else
                M[i][w] = max(M[i - 1][w], tasks[i - 1].penalty() + M[i - 1][w - tasks[i - 1].time()]);
        }
    }



    //the total penaly avoided is in the final slot of the array
    int burned=M[taskAmount][deadline];

    //the penalty for the trash that is stored is the max penalty minus the penalties avoided by burning the trash
    int stored=maxPenalty-burned;

    //cout<<stored_items.front().name()<<endl;

    cout<<"MAX PENALTY: "<<stored<<endl;

    //if the command line signifies to print, do so
    if (print=="-print")
    {
        cout<<"ITEMS STORED: ";
        bool trigger=true;

        //fill the list with all the burned items
        while(taskAmount>0)
        {
            if (M[taskAmount][deadline]!=M[taskAmount-1][deadline])
            {
                burned_items.push_back(tasks[taskAmount-1]);
                deadline-=tasks[taskAmount-1].time();
            }
            taskAmount-=1;
        }

        //the stored items is the difference between all the items and the burned items
        for (TWITS i: all_items)
        {
            if (i.name()!=burned_items.front().name())
            {
                cout<<i.name()<<" ";
                trigger=false; //prove that an item was stored
            }
            else
                burned_items.pop_front();
        }

        if (trigger)
            cout<<"NA";

        cout<<endl;
    }


    return 0;
}
