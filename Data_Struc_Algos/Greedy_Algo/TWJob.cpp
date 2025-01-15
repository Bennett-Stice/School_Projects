/**
 * @author Bennett Stice
 * @date 3/14/2024
 */


#include "TWJob.hpp"

using namespace std;

//sets job values from a file
std::istream&  operator>> (std::istream &is, TWJob &job)
{
  is >> job._name;
  is >> job._penalty;
  is >> job._deadline;

  return is;
}
