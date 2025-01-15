/**
 * @author Bennett Stice
 * @date 3/14/2024
 */

#ifndef _TW_JOB_HPP_
#define _TW_JOB_HPP_

#include <iostream>

class TWJob
{
private:
  std::string _name;  // identifier for job
  int _penalty;        // job length
  int _deadline;      // job deadline time
public:
    //constructors
    TWJob(): _name(), _penalty(-1), _deadline(-1) {}
    TWJob(const std::string &name, int penalty, int deadline)
    : _name(name), _penalty(penalty), _deadline(deadline) {}

    // accessors
    const std::string& name() const {return _name;}
    int penalty() const {return _penalty;}
    int deadline() const {return _deadline;}

    //read in values from a file
    friend std::istream&  operator>> (std::istream &is, TWJob &job);

};

#endif
