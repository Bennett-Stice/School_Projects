/**
 * @author Bennett Stice
 * @date 3/29/2024
 */

#ifndef _PointPair_HPP_
#define _PointPair_HPP_

#include <iostream>
#include "DnC.hpp"

class PointPair
{
private:
    double _dist; //distance between the pair
    DnC _point1;  //first point
    DnC _point2;  //second point
public:
    //constructors
    PointPair(): _dist(1000), _point1(), _point2() {}
    PointPair(double dist, DnC point1,DnC point2)
    : _dist(dist), _point1(point1), _point2(point2) {}

    // accessors
    double dist() const{return _dist;}
    DnC point1() const{return _point1;}
    DnC point2() const{return _point2;}

};

#endif
