/**
 * @author Bennett Stice
 * @date 4/11/2024
 */


#include "TWITS.hpp"

using namespace std;

//sets job values from a file
std::istream&  operator>> (std::istream &is, TWITS &job)
{
  is >> job._name;
  is >> job._penalty;
  is >> job._time;

  return is;
}
