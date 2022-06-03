#include "callstack.h"

ostream& operator<<(ostream& out, Function_t& s)
{
  out << "Function " << s.name << " with " << s.numArguments << " args and ";
  out << s.numLocals << " locals" ;
  return out;
}

void CallStack::call(Function_t f, int RA, int BP, int *args, int *locals)
{
  /* TO DO! */
  //Arg
  for (int i = 0; i < f.numArguments; i++ ){
    rawStack.push(*args);
    *args++;
  }

  //RA
  rawStack.push(RA);

  //BP
  rawStack.push(BP);

  Stack<int> temp;
  //Local
  for (int i = 0; i < f.numLocals; i++) {
    temp.push(*locals);
    *locals++;
  }
  for (int i = 0; i < f.numLocals; i++) {
    rawStack.push(temp.pop());
  }

  info.push(f);
}

Function_t CallStack::currentFunction(void)
{
  /* TO DO! */
  Function_t temp = info.peek();
  return temp;
}

int CallStack::getLocal(int n)
{
  /* TO DO! */
  try {
    bool b = n > currentFunction().numLocals - 1 || n < 0;
  } catch (InvalidIndex e) {
    e.what();
  }
  
  Stack<int> temp;
  int local;

  //Push locals
  for(int i = 0; i < currentFunction().numLocals - n; i++)
  {
    temp.push(rawStack.pop());
  }

  //save value to local
  local = temp.peek();

  //Return to normal.
  for(int i = 0; i < currentFunction().numLocals - n; i++)
  {
    rawStack.push(temp.pop());
  }

  return local;
}

void CallStack::setLocal(int n, int val)
{
  /* TO DO! */
  InvalidIndex e;
  if(n > currentFunction().numLocals - 1 || n < 0)
  {
    throw e;
  }

  Stack<int> temp;
  int local;

  //Push locals
  for(int i = 0; i < currentFunction().numLocals - (n + 1); i++)
  {
    temp.push(rawStack.pop());
  }

  //Remove old local and add new one
  rawStack.pop();
  rawStack.push(val);
  
  //Return to normal
  while(temp.empty() != true)
  {
    rawStack.push(temp.pop());
  }
}

int CallStack::getArg(int n)
{
 /* TO DO! */

  try {
    bool b = n > currentFunction().numArguments - 1 || n < 0;
  } catch (InvalidIndex e) {
    e.what();
  }

  Stack<int> temp;
  int arg;

  //Push locals
  for(int i = 0; i < currentFunction().numLocals; i++)
  {
    temp.push(rawStack.pop());
  }
  
  //Push BP
  temp.push(rawStack.pop());
  
  //Push RA
  temp.push(rawStack.pop());

  
  //Push Args
  for(int i = 0; i < currentFunction().numArguments - (n + 1); i++)
  {
    temp.push(rawStack.pop());
  }

  //save value to arg
  arg = rawStack.peek();


  //Return to normal
  while(temp.empty() != true)
  {
    rawStack.push(temp.pop());
  }

  return arg;
}

void CallStack::setArg(int n, int val)
{
  /* TO DO! */
  InvalidIndex e;
  if(n > currentFunction().numArguments - 1 || n < 0)
  {
    throw e;
  }
 

 Stack<int> temp;
  int arg;

  //Push locals
  for(int i = 0; i < currentFunction().numLocals; i++)
  {
    temp.push(rawStack.pop());
  }
  
  //Push BP
  temp.push(rawStack.pop());
  
  //Push RA
  temp.push(rawStack.pop());

  //Push Args
  for(int i = 0; i < currentFunction().numArguments - (n + 1); i++)
  {
    temp.push(rawStack.pop());
  }

  //Remove old arg and add new one.
  rawStack.pop();
  rawStack.push(val);

  //Return to normal
  while(temp.empty() != true)
  {
    rawStack.push(temp.pop());
  }
}

int CallStack::getBP()
{
  /* TO DO! */
  Stack<int> temp;
  int BP;

  //Push locals
  for(int i = 0; i < currentFunction().numLocals; i++)
  {
    temp.push(rawStack.pop());
  }

  //save value to BP
  BP = rawStack.peek();

  //Return to normal
  while(temp.empty() != true)
  {
    rawStack.push(temp.pop());
  }

  return BP;
}

int CallStack::getRA()
{
    /* TO DO! */
  Stack<int> temp;
  int RA;

  //Push locals
  for(int i = 0; i < currentFunction().numLocals; i++)
  {
    temp.push(rawStack.pop());
  }
  
  //Push BP
  temp.push(rawStack.pop());
  
  //save value to RA
  RA = rawStack.peek();

  //Return to normal
  while(temp.empty() != true)
  {
    rawStack.push(temp.pop());
  }

  return RA;
}

void CallStack::do_return(void)
{
  /* TO DO! */
  //pop all the element of the current function in rawStack
  for(int i = 0; i < currentFunction().numArguments + currentFunction().numLocals + 2; i++) {
    rawStack.pop();
  }

  //pop the current function name so it returns to the last function name
  info.pop();
}

ostream& operator<<(ostream& out, CallStack& s)
{
  /* TO DO! */
  //print locals
  for (int i = 0; i < s.currentFunction().numLocals; i++) {
    out << s.getLocal(i) << " Local " << abs(s.currentFunction().numLocals - i - 1) << " for " << s.currentFunction().name << endl;
  }

  //print bp and ra
  out << s.getBP() << " BP for " << s.currentFunction().name << endl;
  out << s.getRA() <<  " RA for " << s.currentFunction().name << endl;
  
  //print args
  for (int i = 0; i < s.currentFunction().numArguments; i++) {
    out << s.getArg(i) << " Arg " << i << " for " << s.currentFunction().name << endl;
  }
  return out;
}