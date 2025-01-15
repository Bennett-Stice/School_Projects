/**
 * @author Bennett Stice
 * @date 3/29/2024
 */


#include "DnC.hpp"

using namespace std;

//sets point values from a file
std::istream&  operator>> (std::istream &is, DnC &point)
{
  is >> point._name;
  is >> point._Xpos;
  is >> point._Ypos;

  return is;
}
