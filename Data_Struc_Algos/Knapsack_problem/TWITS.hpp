/**
 * @author Bennett Stice
 * @date 4/11/2024
 */

#ifndef _TWITS_HPP_
#define _TWITS_HPP_

#include <iostream>

class TWITS
{
private:
  std::string _name;  // identifier for job
  int _penalty;        // job length
  int _time;      // job deadline time
public:
    //constructors
    TWITS(): _name(), _penalty(-1), _time(-1) {}
    TWITS(const std::string &name, int penalty, int time)
    : _name(name), _penalty(penalty), _time(time) {}

    // accessors
    const std::string& name() const {return _name;}
    int penalty() const {return _penalty;}
    int time() const {return _time;}

    //read in values from a file
    friend std::istream&  operator>> (std::istream &is, TWITS &job);

};

#endif
