/**
 * @author Bennett Stice
 * @date 3/14/2024
 */


#include "TWJob.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

bool compareByPenalty(const TWJob &t1, const TWJob &t2)
{
    return t1.penalty() > t2.penalty();
}

int main (int argc,char* argv[])
{
    // pull in filename from command prompt.
    string fName = argv[1];

    // build input stream from filename
    ifstream ifile(fName);

    list<TWJob> tasks; // list of all jobs

    TWJob task; // next job in input file

    // for each job read from input file, add that job to list of all jobs
    ifile>>task;
    while(ifile)
    {
        tasks.push_back(task);
        ifile>>task;
    }

    //sort the tasks by the size of their penalty descending
    tasks.sort(compareByPenalty);

    int maxDeadline=100000;

    int minPenalty = 0;

    //create a vector list of the slots where they are initialized as all being open
    vector<bool> slotAvailable(maxDeadline, true);

    for (TWJob &job : tasks)
    {
        bool scheduled = false;

        //if for some reason the jobs deadline is greater than the max deadline reset the start position
        int starter = min(job.deadline() - 1, maxDeadline - 1);

        // Try to schedule the job to be the deadline if possible and if not try the slots before it
        for (int i = starter; i >= 0; --i)
        {
            //if the slot is open, close it and denote that the job has been scheduled
            if (slotAvailable[i])
            {
                slotAvailable[i] = false;
                scheduled = true;
                break;
            }
        }

        // If unable to schedule, add penalty
        if (!scheduled)
        {
            minPenalty += job.penalty();
        }
    }

    cout << "Min Penalty = " <<minPenalty<<endl;

    return 0;
}
