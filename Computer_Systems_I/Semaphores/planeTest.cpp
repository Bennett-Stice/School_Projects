/*
  add in -lncurses
  maybe -lnthread aswell
  maybe ncureses -devel
  
 * FILE: planeTest.cpp
 * Author: S. Blythe
 * DATE: 8/2023  
 *
 * gives an example usage of the methods found in the AirportAnimator class. 
 * Please do not misconstrue this is a partial solution to the overall project. 
 */
#include "AirportAnimator.hpp"

#include <unistd.h>

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  unsigned int planeNum;
  if (! (argc==2 &&  (planeNum=atoi(argv[1])) < 8)  )
    {
      cerr << "Plane number not properly specified.";
      srand(time(NULL));
      planeNum = rand()%8;
      cerr << " Set to:" << planeNum << endl;
      sleep(3);
    }

  cerr << "Plane:" << planeNum << endl;
  cerr.flush();
  sleep(3);
  
  // do not include anything before this line
  AirportAnimator::init();

  //maybe need a wait here
  for(int passenger=1; passenger<=12; passenger++)
    {
      AirportAnimator::updatePassengers(planeNum, passenger);
      sleep(1);
    }
  
  AirportAnimator::updateStatus(planeNum, "TAXI");
  AirportAnimator::taxiOut(planeNum);

  //wait here
  AirportAnimator::updateStatus(planeNum, "TKOFF");
  AirportAnimator::takeoff(planeNum);
  //signal here

  AirportAnimator::updateStatus(planeNum,"TOUR");
  sleep(10);

  AirportAnimator::updateStatus(planeNum,"LNDRQ");
  sleep(2);

  // wait here
  AirportAnimator::updateStatus(planeNum,"LAND");
  AirportAnimator::land(planeNum);
  //signal here
  
  AirportAnimator::updateStatus(planeNum, "TAXI");
  AirportAnimator::taxiIn(planeNum);

  AirportAnimator::updateStatus(planeNum, "DEPLN");
  for(int passenger=11; passenger>=0; passenger--)
    {
      AirportAnimator::updatePassengers(planeNum, passenger);
      sleep(1);
    }
  
  AirportAnimator::updateStatus(planeNum, "DEPLN");
  
  //maybe a signal here
  
  AirportAnimator::updateTours(1);
  sleep(2);
  
  AirportAnimator::end();

}
