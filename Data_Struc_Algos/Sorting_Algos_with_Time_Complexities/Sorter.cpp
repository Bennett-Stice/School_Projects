#include "Sorter.hpp"

#include <iostream>
#include <list>
#include <cstdlib>
#include <string>

using namespace std;


list<string> bubbleSort(list<string>& input)
{
    list<string> placeholder; //create list of strings that will hold a temp list
    bool sorted=true; //bool to tell if a swap has been made in a round
    string first, second; //strings to hold nodes that are being compared

    while(sorted)
    {
        sorted=false; //set sorted to false
        placeholder.clear(); //clear out temp list

        first=input.front(); //put first spot of the list into temp list
        input.pop_front(); //get rid of first spot

        //continue round until there is no more input list
        while(input.size()>=1)
        {
            //load second string to compare and pop it off the front of the list
            second=input.front();
            input.pop_front();

            //make swap if first is greater than second
            if (first>second)
            {
                placeholder.push_back(second);
                sorted=true;
            }

            else
            {
                placeholder.push_back(first);
                first=second;
            }
        }
        placeholder.push_back(first); //add last element to temp list
        input=placeholder; //readjust for next round
    }

    return placeholder;

}

//helper for merge sort
list<string> merge(list<string>& A, list<string>& B)
{
    //create output list
    list<string> mergedList;

    //continue until one list is empty
    while(!A.empty() && !B.empty())
    {
        //compare the front of both list
        if (A.front()<B.front())
        {
            mergedList.push_back(A.front());
            A.pop_front();
        }
        else
        {
            mergedList.push_back(B.front());
            B.pop_front();
        }
    }

    //if one list is empty before the other add the rest to the end of the merged List
    while(!A.empty())
    {
        mergedList.push_back(A.front());
        A.pop_front();
    }

    while(!B.empty())
    {
        mergedList.push_back(B.front());
        B.pop_front();
    }

    return mergedList;
}

list<string> mergeSort(list<string>& input)
{
    if (input.size()<=1)
    {
        return input;
    }

    else
    {
        list<string> frontHalf,backHalf; //create two list
        int halfSize=input.size()/2;

        //put the frong half of the input into 1 list
        for (int i=0;i<halfSize;i++)
        {
            frontHalf.push_back(input.front());
            input.pop_front();
        }

        //put the rest in the backHalf
        backHalf=input;

        //continue sorting until the list only have one node
        frontHalf=mergeSort(frontHalf);
        backHalf=mergeSort(backHalf);
        input=merge(frontHalf,backHalf); //glue the two list together
    }

    return input;
}


list<string>& quickSort(list<string>& input)
{
    //continue until list only has one node
    if (input.size()<=1)
    {
        return input;
    }

    //load in the front of the input to be the pivot point
    string E = input.front();
    input.pop_front();

    //create a less than list and greater than list
    list<string> L,G;

    while(input.size()>=1)
    {
        //if input is less than the pivot put it in less than and vice versa for greater than
        if (input.front()<E)
        {
            L.push_back(input.front());
            input.pop_front();
        }
        else
        {
            G.push_back(input.front());
            input.pop_front();
        }
    }

    //sort the two list using recursion
    quickSort(L);
    quickSort(G);

    //combine the list for the output list
    for (auto val:L)
    {
        input.push_back(val);
    }

    input.push_back(E);

    for (auto val:G)
    {
        input.push_back(val);
    }

    return input;
}




list<string> heapSort(list<string>& input)
{

    //determine the size of the list
    int size=input.size();
    string* heap= new string[size+1];
    heap[0]="1";

    int checkPos;

    //create heap
    for (int i=1;i<=size;i++)
    {
        //put the next node into the last spot in the heap
        heap[i]=input.front();
        input.pop_front();

        //set the check position to the end of the heap currently
        checkPos=i;

        //continue checking till the the top of the heap
        while(checkPos!=0)
        {
            if (heap[checkPos]<heap[checkPos/2])
            {
                string buffer=heap[checkPos/2];
                heap[checkPos/2]=heap[checkPos];
                heap[checkPos]=buffer;
            }
            checkPos=checkPos/2;
        }
    }

    list<string> output;

    int bigIndex=size;
    int index;

    //
    for (int i=1;i<=size;i++)
    {
        //put the top of the heap into the back of the list
        output.push_back(heap[1]);

        //swap the back of the list to the front
        heap[1]=heap[bigIndex];
        heap[bigIndex]="~";

        index=1;
        bool stop=true;

        //continue checking down the list making the necessary swaps
        while(index<=bigIndex/2-1 && stop)
        {
            if (heap[index]>heap[index*2] || heap[index]>heap[index*2+1])
            {
                if(heap[index*2]<heap[index*2+1])
                {
                    string buffer=heap[index];
                    heap[index]=heap[index*2];
                    heap[index*2]=buffer;
                    index=index*2;
                }

                else
                {
                    string buffer=heap[index];
                    heap[index]=heap[index*2+1];
                    heap[index*2+1]=buffer;
                    index=index*2+1;
                }
            }

            else
            {
                stop=false;
            }
        }

        bigIndex--;
    }

    delete[] heap;

    return output;
}

//use built in sort system
list<string> sysSort(list<string>& input)
{
    input.sort();
    return input;
}
