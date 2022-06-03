/* 
Simulates the x86 call stack
DO NOT MODIFY THIS HEADER FILE. You will not submit this file.
*/

#ifndef __CALLSTACK_H
#define __CALLSTACK_H

#include "stack.hpp"

typedef struct 
{
  char *name;
  int numArguments;  //Set to -1 if no args
  int numLocals;  //Set to -1 if no locals
  
} Function_t;

/*
    EXAMPLE STACK LAYOUT

    localn
    ...
    local3
    local2
    local1
    BP
    RA
    arg1
    arg2
    arg3
    ...
    argn
    localn of previous function
    ...
    local1 of previous function
    BP of previous function
    ...

*/

class CallStack
{
private:
    Stack<int> rawStack;  //Contains the raw data -- what we would see in a real stack
    Stack<Function_t> info;  //Stores extra info on the functions called.
public:
    //To call the function, push the values onto the stack in the layout seen above and
    //   store the function details in info.
    //Note that args and locals are an array of ints
    void call(Function_t f, int RA, int BP, int *args, int *locals);
    
    //Return the function currently being run.
    Function_t currentFunction(void);  
    
    //Note: in order to access the locals/args of the current function, you'll need to 
    //  pop off the previous values, get/modify the desired local/arg,
    //  and then restore the stack back to how it is was.
    //  This is inefficient and unrealistic, but it serves our purposes for the simulation.
    //  Also note that this is 0-indexed, so n=0 returns the first arg
    int getLocal(int n);  //Returns the value of the nth local
    void setLocal(int n, int val);  //Sets the value of the nth local
    int getArg(int n);  //Returns the value of the nth arg
    void setArg(int n, int val);  //Sets the value of the nth arg
    int getBP();  //Returns the value of the BP
    int getRA();  //Returns the value of the RA

    //Returns from the function currently being "run". Remove all values from the stack 
    //  related to the current function
    void do_return(void);
};

//Prints function details
ostream& operator<<(ostream& out, Function_t& s);

//An exception thrown when one of the getter/setters is called with an invalid n
struct InvalidIndex : public exception {
   const char * what () const throw () {
      return "getLocal, setLocal, getArg, or setArg called with invalid n";
   }
};

//Prints out the stack in two columns, the value and a label for that value
//Two examples output with stack containing two functions,
// myFunction2 (2 locals, 1 arg) and function1 (1 local, 2 args):
/*
10 Local 1 for myFunction2
200 Local 0 for myFunction2
2 BP for myFunction2
1000 RA for myFunction2
30 Arg 0 for myFunction2


32 Local 0 for myFunction1
300 BP for myFunction1
2000 RA for myFunction1
50 arg 0 for myFunction1
42 arg 1 for myFunction1
*/
ostream& operator<<(ostream& out, CallStack& s);

#endif