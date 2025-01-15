/*
 * @author bennett stice
 * @date 11/7/2023
 */


#include "AirportAnimator.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <cerrno>
#include <sys/sem.h>



using namespace std;

//declare the following global variables so they can be used in each thread
int tripNum;
int passNum;
int pass_sem;
int runway_sem;

struct sembuf pass_wait_com[1];
struct sembuf pass_sig_com[1];
struct sembuf run_wait_com[1];
struct sembuf run_sig_com[1];

void* doThread(void *arg)
{
    int *planeNum= (int *) arg;
    int passes=0;

    //keep going until you complet the needed number of passes.
    while (passes<tripNum)
    {
        //Load up the passengers
        AirportAnimator::updateStatus(*planeNum, "BOARD");
        for (int pass=1;pass<=12;pass++)
        {

            semop(pass_sem,pass_wait_com,1); //if we are out of available passengers wait till their are some.
            AirportAnimator::updatePassengers(*planeNum, pass);
            sleep(1+rand()%2);
        }

        //taxi out to the runway
        AirportAnimator::updateStatus(*planeNum, "TAXI");
        AirportAnimator::taxiOut(*planeNum);

        // wait here to make sure the runway is open
        semop(runway_sem, run_wait_com, 1);
        AirportAnimator::updateStatus(*planeNum, "TKOFF");
        AirportAnimator::takeoff(*planeNum);

        //signal here to open the runway
        semop(runway_sem, run_sig_com, 1);

        AirportAnimator::updateStatus(*planeNum,"TOUR");
        sleep(15+rand()%31);

        AirportAnimator::updateStatus(*planeNum,"LNDRQ");
        sleep(2);

        // wait here to make sure the runway is open
        semop(runway_sem, run_wait_com, 1);

        AirportAnimator::updateStatus(*planeNum,"LAND");
        AirportAnimator::land(*planeNum);

        //signal here to open the runway
        semop(runway_sem, run_sig_com, 1);

        //Taxi back to gate
        AirportAnimator::updateStatus(*planeNum, "TAXI");
        AirportAnimator::taxiIn(*planeNum);

        //Kick passengers off the plane
        AirportAnimator::updateStatus(*planeNum, "DEPLN");
        for(int passenger=11; passenger>=0; passenger--)
        {
            AirportAnimator::updatePassengers(*planeNum, passenger);
            sleep(1);
            semop(pass_sem, pass_sig_com, 1); //signal here to add a passenger back in the pot
        }

        //increment the amount of tours thus far
        passes++;
        AirportAnimator::updateTours(passes);
        sleep(2);

    }


    return NULL;
}

int main(int argc, char *argv[])
{
    //set amount of passengers and amount of trips from the command line.
    passNum=atoi(argv[1]);
    tripNum=atoi(argv[2]);


    //make our threads
    pthread_t plane0, plane1, plane2, plane3, plane4, plane5, plane6, plane7;

    //passenger key value is 204
    pass_sem=semget(204,passNum,0);
    if (pass_sem==-1)
    {
        pass_sem = semget(204,passNum,IPC_CREAT|IPC_EXCL|0666);

        if (pass_sem==-1)
        {
            cerr<<"semget()  passengers failed with errno = " <<errno<<endl;
            return 2;
        }
    }

    //runway key value is 201
    runway_sem=semget(201,1,0);
    if (runway_sem==-1)
    {
        runway_sem = semget(201,1,IPC_CREAT|IPC_EXCL|0666);

        if (runway_sem==-1)
        {
            cerr<<"semget() failed with errno = " <<errno<<endl;
            return 3;
        }
    }

    //make the command array attributes
    pass_wait_com[0].sem_num = 0;
    pass_wait_com[0].sem_op  =-1;
    pass_wait_com[0].sem_flg = 0;

    pass_sig_com[0].sem_num = 0;
    pass_sig_com[0].sem_op  =1;
    pass_sig_com[0].sem_flg = 0;

    run_wait_com[0].sem_num = 0;
    run_wait_com[0].sem_op  =-1;
    run_wait_com[0].sem_flg = 0;

    run_sig_com[0].sem_num = 0;
    run_sig_com[0].sem_op  =1;
    run_sig_com[0].sem_flg = 0;

    //guarantee that the semaphores start at the correct value
    semctl(pass_sem, 0 /*index #*/,   SETVAL, passNum);
    semctl(runway_sem, 0 /*index #*/,   SETVAL, 1);

    //start up the animation
    AirportAnimator::init();

    //create the threads for each of the planes
    int id0=0;
    int errCode = pthread_create(&plane0, NULL, doThread, (void *) &id0);
    if (errCode==-1)
        cerr << "pplanecreate() failed"<<endl;

    int id1=1;
    errCode = pthread_create(&plane1, NULL, doThread, (void *) &id1);
    if (errCode==-1)
        cerr << "pplanecreate() failed"<<endl;

    int id2=2;
    errCode = pthread_create(&plane2, NULL, doThread, (void *) &id2);
    if (errCode==-1)
        cerr << "pthreadcreate() failed"<<endl;

    int id3=3;
    errCode = pthread_create(&plane3, NULL, doThread, (void *) &id3);
    if (errCode==-1)
        cerr << "pthreadcreate() failed"<<endl;

    int id4=4;
    errCode = pthread_create(&plane4, NULL, doThread, (void *) &id4);
    if (errCode==-1)
        cerr << "pthreadcreate() failed"<<endl;

    int id5=5;
    errCode = pthread_create(&plane5, NULL, doThread, (void *) &id5);
    if (errCode==-1)
        cerr << "pthreadcreate() failed"<<endl;

    int id6=6;
    errCode = pthread_create(&plane6, NULL, doThread, (void *) &id6);
    if (errCode==-1)
        cerr << "pthreadcreate() failed"<<endl;

    int id7=7;
    errCode = pthread_create(&plane7, NULL, doThread, (void *) &id7);
    if (errCode==-1)
        cerr << "pthreadcreate() failed"<<endl;

    //join the threads together
    pthread_join(plane0, NULL);
    pthread_join(plane1, NULL);
    pthread_join(plane2, NULL);
    pthread_join(plane3, NULL);
    pthread_join(plane4, NULL);
    pthread_join(plane5, NULL);
    pthread_join(plane6, NULL);
    pthread_join(plane7, NULL);

    //end the animation
    AirportAnimator::end();




    return 0;
}
