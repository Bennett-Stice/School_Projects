// !!!!!! You will have to add code inside of this class. Some of
//        the code provided here is designed to help you, but you
//         do not need to use it if you do not want to. 

/**
 * @author Bennett Stice
 * @date 2/12/2024
 */

#include "Statement.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <list> //I added this to help me out

using namespace std;

int __nextSnum=0; // keeps track of the next statement number to use. 
int __paramValue; // this is a global to help with passing a parameter. 

/****
 **** If you are following project specifications, then you will likley
 **** find this function quite useful. When given an ActivationRecord
 **** (pointer) and a string containing an operand, this function returns
 **** the operand's value (as found in the ActivationRecord.)
 ****/
int getValue(ActivationRecord *ar, const std::string &operand)
{
  if (operand == "$$") // looking for the parameter
    return ar->parameterValue();
  else if (isdigit(operand[0]) || operand[0]=='-') // constant value (int)
    {
      return atoi(operand.c_str());
    }
  else // ID
    {
      // find the variable in the activation record
      Variable *var = (Variable *)  ar->getVariable(operand);

      // if the variable was not found, let the user know. 
      if (var==NULL)
	{
	  cerr << "Attempt to use an uninitialized variable: "
	       << operand << endl;
	  return 0;
	}
      else
	return var->value(); //return value of the associated variable 
    }
}

/****
 **** If you are following project specifications, then you will likley
 **** find this function quite useful. When given an ActivationRecord
 **** (pointer), a string containing an variable name, and a new value,
 **** this function sets that variable to the new value (in the associated
 **** ActivationRecord.) If the variable isn't found in the Activation
 ***  Record, it is added to the ActivationRecord.
 ****/
void setValue(ActivationRecord *ar, const std::string &varName, int toVal)
{
  if (varName == "$$") // parameter
    ar->parameterValue() = toVal;
  else // anything else must be a variable
    {
      // get the Variable from the ActivationRecord
      Variable *var = (Variable *)  ar->getVariable(varName);

      // no such variable? Means we need to add it to the ActivationRecord
      if (var==NULL)
	{
	  ar->addVariable(varName);
	  var = (Variable *)  ar->getVariable(varName);
	}

      // now that we know we have a variable, set its value ... 
      var->value()=toVal;
    }
}

//
// ********   YOU MUST CODE LARGE PARTS OF THIS !!!!   **********
//
// Executes a statement. See the project handout for details. Some
//  initial statements are given as examples.
//
//     withStack - The ActivationRecord (i.e. execution)  stack to use
//     ft - the table of function names & starting points
//
//  *should return the statement number (address) of the next statement to run
int
Statement::execute(Stack &withStack, const FunctionTable &ft) const
{
  // the next statement will be 1 after this one ... with the exception
  //  of calls, rets, and skips (see project handout.)
  int nextAddr = _snum+1; 

  if (_operation=="printS") // print string. 
    {
      cout << _operands.front();
    }
  else if (_operation=="printN") // print number
    {
      // get the value to print from the current activation record. 
      int valueOfN = getValue(withStack.top(), _operands.front());

      // print that value
      cout << valueOfN;
    }
  else if (_operation=="printNL") // drop down a line in output
    {
      cout << endl; // yep, it's that simple!
    }

  else if (_operation=="call") //call a new function
  {
    string functionName =_operands.front(); //load in function name

    ActivationRecord* nextCall= new ActivationRecord(functionName,nextAddr,__paramValue); //create new Activation Record
    withStack.push(nextCall); //push it on the Stack
    nextAddr=ft.lookup(functionName).firstInstruction(); //reset the address to the location of the function
  }

  else if (_operation=="ret") //set up next address
  {
    ActivationRecord* nextAR = withStack.pop(); //pop the top of the stack
    nextAddr = nextAR->returnAddress(); //reset the next Address
  }

  else if (_operation == "retv")
  {
    ActivationRecord* peekAR = withStack.peek(); //look at the second thing on the stack
    peekAR->incomingReturnValue()=getValue(withStack.top(),_operands.front()); //set it's value to the operand value

    ActivationRecord* nextAR=withStack.pop(); //pop of the top
    nextAddr= nextAR->returnAddress(); //reset the next Address
  }

  else if (_operation == "storet") //store a value in the variable in the operands
  {
    ActivationRecord* nextAR = withStack.top();
    setValue(nextAR,_operands.front(),nextAR->incomingReturnValue());
  }

  else if (_operation == "param") //set the param value
  {
    __paramValue=getValue(withStack.top(),_operands.front());
  }

  else if (_operation=="sub")//do subtraction
  {
    std::list<std::string> operandsCopy = _operands; // Create a non-const copy of the list

    int a = getValue(withStack.top(),operandsCopy.front()); //set a value
    operandsCopy.pop_front(); //get rid of the top

    int b = getValue(withStack.top(),operandsCopy.front()); //set b value
    operandsCopy.pop_front(); //get rid of the top

    std::string c = operandsCopy.front(); //create c to be the variable

    setValue(withStack.top(), c, a-b);//set c to be a-b
  }

  else if (_operation=="add")//do addition
  {
    std::list<std::string> operandsCopy = _operands; // Create a non-const copy of the list

    int a = getValue(withStack.top(),operandsCopy.front()); //set a value
    operandsCopy.pop_front(); //get rid of the top

    int b = getValue(withStack.top(),operandsCopy.front()); //set b value
    operandsCopy.pop_front(); //get rid of the top

    std::string c = operandsCopy.front(); //create c to be the variable

    setValue(withStack.top(), c, a+b);//set c to be a+b
  }

  else if (_operation=="mul")//do multiplication
  {
    std::list<std::string> operandsCopy = _operands; // Create a non-const copy of the list

    int a = getValue(withStack.top(),operandsCopy.front()); //set a value
    operandsCopy.pop_front(); //get rid of the top

    int b = getValue(withStack.top(),operandsCopy.front()); //set b value
    operandsCopy.pop_front(); //get rid of the top

    std::string c = operandsCopy.front(); //create c to be the variable

    setValue(withStack.top(), c, a*b);//set c to be a*b
  }

  else if (_operation=="div")//do division
  {
    std::list<std::string> operandsCopy = _operands; // Create a non-const copy of the list

    int a = getValue(withStack.top(),operandsCopy.front()); //set a value
    operandsCopy.pop_front(); //get rid of the top

    int b = getValue(withStack.top(),operandsCopy.front()); //set b value
    operandsCopy.pop_front(); //get rid of the top

    std::string c = operandsCopy.front(); //create c to be the variable

    setValue(withStack.top(), c, a/b);//set c to be a/b
  }

  else if (_operation == "skipz") //skip over some statements
  {
    std::list<std::string> operandsCopy = _operands; // Create a non-const copy of the list

    int first = getValue(withStack.top(),operandsCopy.front()); //enter in first operand
    operandsCopy.pop_front(); //discard the top

    int second = getValue(withStack.top(),operandsCopy.front()); //enter the second operand

    //if first operand is zero do skips
    if (first==0)
    {
      nextAddr+=second;
    }

  }

  else if (_operation == "skipnz")
  {
    std::list<std::string> operandsCopy = _operands; // Create a non-const copy of the list

    int first = getValue(withStack.top(),operandsCopy.front()); //enter in first operand
    operandsCopy.pop_front(); //discard the top

    int second = getValue(withStack.top(),operandsCopy.front()); //enter the second operand

    //if first operand is not zero then do skips
    if (first!=0)
    {
      nextAddr+=second;
    }
  }

  else if (_operation == "read") //read in a value and set the operand variable equal to it
  {
    int val;
    cin>>val;
    setValue(withStack.top(),_operands.front(),val);
  }

  else if (_operation == "dump") //print out the Stack
  {
    cout<<withStack<<endl;
  }

  else
    {
      cout << _operation << ": not implememnted" << endl;
    }
  return nextAddr;
}

// prints out this statement to the specified stream (overloads <<) 
ostream& operator<<(ostream &os, const Statement &s)
{
  // print the statement number in the specified width. 
  os.width(5);
  os << s._snum << " ";

  // print the operation
  os << s._operation << '\t';

  // print each operand .. 
  list<string>::const_iterator lsci = s._operands.begin();
  for (int i=0; i< s._operandCount; i++)
    {
      os <<  *lsci << " ";

      lsci++;
    }

  return os;
}
