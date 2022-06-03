#include "callstack.h"

/*
This is a short program to test your callstack. Note that this does not cover all of the capabilities
of the callstack, and the TAs will test other examples. The correct output can be found in output.txt

Feel free to modify this file for additional testing.  You will not submit this file.
*/

int main()
{
    CallStack test;
    char name1[] = "myFunction1";
    char name2[] = "myFunction2";
    Function_t myFunction1 = {name1, 2, 1};  //Using the functions from the printing example
    Function_t myFunction2 = {name2, 1, 2};

    int myFunc1Args[] = {50, 42};
    int myFunc1Locals[] = {32};
    int myFunc2Args[] = {30};
    int myFunc2Locals[] = {200, 10};

    test.call(myFunction1, 2000, 300, myFunc1Args, myFunc1Locals);
    cout << test;  //Print stack for myFunction1
    test.call(myFunction2, 1000, 2, myFunc2Args, myFunc2Locals);


    cout << "------------------------" << endl;
    cout << test;  //Print stack for myFunction2
    test.do_return();
    cout << "------------------------" << endl;
    cout << test;  //Print stack for myFunction1 again

    cout << "------------------------" << endl;
    test.setArg(1, 1111);
    try{
        test.setArg(2, 1111);
    }
    catch (InvalidIndex e)
    {
        cout << e.what() << endl;  //Should catch an exception
    }

    test.setLocal(0, 2222);
    try{
        test.setLocal(1, 2222);
    }
    catch (InvalidIndex e)
    {
        cout << e.what() << endl;  //Should catch an exception
    }

    //Check that changes were made
    cout << "------------------------" << endl;
    cout << test;  //Print stack for myFunction1 again

    return 0;
}