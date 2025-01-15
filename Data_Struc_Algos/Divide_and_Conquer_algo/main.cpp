/**
 * @author Bennett Stice
 * @date 3/29/2024
 */

#include <iostream>
#include <fstream>
#include <list>
#include <cmath>
#include <limits>


#include "DnC.hpp"
#include "PointPair.hpp"

using namespace std;

//helpers for sorting
bool compareByXpos(const DnC &p1, const DnC &p2)
{
    return p1.Xpos()<p2.Xpos();
}

bool compareByYpos(const DnC &p1, const DnC &p2)
{
    return p1.Ypos()<p2.Ypos();
}

//function that finds the closest pair point and return it.
PointPair Closest_Pair(list<DnC> inputList,int size)
{
    //3 base cases
    //if there is one point in the inputed list return the largest possible distance
    if (inputList.size()==1)
    {
        double maxdouble=numeric_limits<double>::max();
        return PointPair(maxdouble,inputList.front(),inputList.front());
    }

    //if there is 2 points in the inputed list return them as a point pair
    if (inputList.size()==2)
    {
        DnC point1=inputList.front();
        DnC point2=inputList.back();
        return PointPair(sqrt(pow(point1.Xpos()-point2.Xpos(),2)+pow(point1.Ypos()-point2.Ypos(),2)),point1,point2);
    }

    //if there is 3 points in the inputed list return the point pair with the smallest distance between 2 points
    if (inputList.size()==3)
    {
        //define 3 points from the list
        DnC point1=inputList.front();
        inputList.pop_front();
        DnC point2=inputList.front();
        DnC point3=inputList.back();

        //create all 3 possible pair points between each point
        PointPair pair12(sqrt(pow(point1.Xpos()-point2.Xpos(),2)+pow(point1.Ypos()-point2.Ypos(),2)),point1,point2);
        PointPair pair13(sqrt(pow(point1.Xpos()-point3.Xpos(),2)+pow(point1.Ypos()-point3.Ypos(),2)),point1,point3);
        PointPair pair23(sqrt(pow(point2.Xpos()-point3.Xpos(),2)+pow(point2.Ypos()-point3.Ypos(),2)),point2,point3);

        //set the smallest distance of the pairs
        double minDist=min(pair12.dist(),min(pair13.dist(),pair23.dist()));


        //find which distance is the smallest and return it
        if (pair12.dist()==minDist)
            return pair12;
        else if (pair13.dist()==minDist)
            return pair13;
        else
            return pair23;
    }

    //create a list of points to the left of the middle line
    list<DnC> Left;

    //load in half of the points into the left side list
    for (int i=0;i<size/2;i++)
    {
        Left.push_back(inputList.front());
        inputList.pop_front();
    }

    //load in the rest of the values into the right side list
    list<DnC> Right = inputList;

    //find the closest pair on the left and right side
    PointPair Left_pair=Closest_Pair(Left,Left.size());
    PointPair Right_pair=Closest_Pair(Right,Right.size());


    //remember which of the sides distances is smaller
    double Min_Sides_dist = min(Left_pair.dist(),Right_pair.dist());
    PointPair Min_Sides_Pair;

    //set the pair with the smaller distance to the Min_Sides_Pair
    if (Left_pair.dist()==Min_Sides_dist)
        Min_Sides_Pair=Left_pair;
    else
        Min_Sides_Pair=Right_pair;

    //define the middle Line as the average X distance of the last point in the left side list and the first point in the right side list
    double middleLine=(Left.back().Xpos()+Right.back().Xpos())/2;

    //create a list of points that are in the middle list
    list<DnC> Middle;

    //load in points that are Min_Sides_dist from the middle line
    for (long unsigned int i=0;i<Left.size();i++)
    {
        DnC point = Left.back();
        Left.pop_back();
        if (point.Xpos()>(middleLine-Min_Sides_dist))
            Middle.push_front(point);
        else
            break;
    }

    for (long unsigned int i=0;i<Right.size();i++)
    {
        DnC point = Right.front();
        Right.pop_front();
        if (point.Xpos()<(middleLine+Min_Sides_dist))
            Middle.push_back(point);
        else
            break;
    }

    //sort points by Y position
    Middle.sort(compareByYpos);

    //declare an array of the same size as the Middle List
    DnC *MiddleSection = new DnC[Middle.size()];

    //load in the values from the Middle list into the Midde array
    int counter=0;
    for (DnC i:Middle)
    {
        MiddleSection[counter]=i;
        counter++;
    }


    //set the Middle_dist to equal the Min_Sides_dist
    double Middle_dist=Min_Sides_dist;
    DnC MidPoint1;
    DnC MidPoint2;

    //find the distance between each point and the next 11 spots in the array
    for (long unsigned i=0;i<Middle.size();i++)
    {
        int CompPos=1;
        while (CompPos<11 && i+CompPos<Middle.size())
        {
            //find the distance between the points
            double tempDist = sqrt(pow(MiddleSection[i].Xpos()-MiddleSection[i+CompPos].Xpos(),2)+pow(MiddleSection[i].Ypos()-MiddleSection[i+CompPos].Ypos(),2));

            //if it is less than the Middle distance save the distance and each two points
            if (tempDist<Middle_dist)
            {
                Middle_dist=tempDist;
                MidPoint1=MiddleSection[i];
                MidPoint2=MiddleSection[i+CompPos];
            }
            CompPos++;
        }
    }

    //return the the point pair with smallest distance between them
    if (Middle_dist<Min_Sides_dist)
        return PointPair(Middle_dist,MidPoint1,MidPoint2);
    else
        return Min_Sides_Pair;

}



int main (int argc, char *argv[])
{
    // pull in filename from command prompt.
    string fName = argv[1];

    // build input stream from filename
    ifstream ifile(fName);

    //read in the amount of points that are in the file
    int pointsNum;
    ifile>>pointsNum;

    list<DnC> points; //create a list of all the points

    DnC point; // next point in input file

    // for each job read from input file, add that job to list of all jobs
    ifile>>point;
    for (int i=0;i<pointsNum;i++)
    {
        //add the point to the back of the list and read in the next point
        points.push_back(point);
        ifile>>point;
    }

    //sort by X values
    points.sort(compareByXpos);

    //Find closest pair
    PointPair answer= Closest_Pair(points,pointsNum);

    //print out the smallest distace between two points and what those points are
    cout<<"Min Distance: "<<answer.dist()<<endl<<"Between "<<answer.point1().name()<<" : ("<<answer.point1().Xpos();
    cout<<","<<answer.point1().Ypos()<<") and "<<answer.point2().name()<<" : ("<<answer.point2().Xpos()<<","<<answer.point2().Ypos()<<")"<<endl;



    return 0;
}
