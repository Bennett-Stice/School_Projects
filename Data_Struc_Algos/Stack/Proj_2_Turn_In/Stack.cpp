// Your implementation of the Stack class goes here!!!!
/**
 * @author Bennett Stice
 * @date 2/12/2024
 */

#include "Stack.hpp"

#include <iostream>

using namespace std;

//Remove the value on the top and return it
ActivationRecord*
Stack::pop()
{
    ActivationRecord* firstVal=front();
    pop_front();

    return firstVal;
}

//put the ActivationRecord on the top of the stack
void
Stack::push(ActivationRecord *newAR)
{
    push_front(newAR);
}

//Show whats on the top of the stack
ActivationRecord*
Stack::top() const
{
    ActivationRecord* firstVal=front();
    return firstVal;
}

ActivationRecord*
Stack::peek() const
{
    Stack tempStack(*this); //create a copy
    tempStack.pop_front(); //discard the front of the copy
    return tempStack.front(); //return the second of the copy which is now the front.
}

//if stack is empty return true
bool
Stack::isEmpty() const
{
    return empty();
}

//print out the contents of a stack
std::ostream& operator<<(std::ostream &os, const Stack &s)
{
    Stack tempStack(s);
    while(!tempStack.isEmpty()) //continue until stack is empty
    {
        os<<*tempStack.pop()<<endl;
    }
    return os;
}
