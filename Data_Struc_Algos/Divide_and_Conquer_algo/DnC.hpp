/**
 * @author Bennett Stice
 * @date 3/29/2024
 */

#ifndef _DNC_HPP_
#define _DNC_HPP_

#include <iostream>

class DnC
{
private:
  std::string _name;    // identifier for point
  double _Xpos;         // point's X location
  double _Ypos;         // point's Y location
public:
    //constructors
    DnC(): _name(), _Xpos(-1), _Ypos(-1) {}
    DnC(const std::string &name, float Xpos, float Ypos)
    : _name(name), _Xpos(Xpos), _Ypos(Ypos) {}

    // accessors
    const std::string& name() const {return _name;}
    double Xpos() const {return _Xpos;}
    double Ypos() const {return _Ypos;}

    //read in values from a file
    friend std::istream&  operator>> (std::istream &is, DnC &point);

};

#endif
