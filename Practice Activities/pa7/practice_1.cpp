// Program to check if the user-provided number is a palindrome

// TODO: Fix the bugs and make sure the program runs as expected.
// Provide a brief comment identifying each bug fixed.

#include <iostream>
using namespace std; // added this to allow std namespace functions
bool func(int x); // changed form char to int
int main()
{
        int input;
        cout << "enter an integer please: ";
        cin >> input; // allow user to input a number
        bool returned_val = func(input); // pass input into the function
        if (returned_val) // condition is backwards so I flipped the print statements
        {
                cout << "It is a palindrome" << endl; // added quotes around this
        }
        else
        {
                cout << "It is not a palindrome" << endl; 
        }

        return 0; // added semicolon
}

// the return value of your func should be true / false only
bool func(int n) // changed return type to be boolean. Also only needs to take in one int
{
        int temp = 0; // no need for float given number
        int origonal = n; // adding this to keep track of the origonal value
        while (n != 0) // change to while n != 0
        {
                int remainder = n % 10; //  added a datatype to remainder. also changed to % from /
                n = n / 10;
                temp = temp * 10 + remainder; // added temp =
        }

        return temp == origonal; // simplified the return statement
}

/*
- Added quotes around 'This is not a palindrome' so it is a string
- Changed the type of input to be an int
- Allowed the user to type in an input instead of predefining it
- Changed the return type of func to be a boolean
- func only needs to take in one integer
- changed the input type of the decleration of func to be an int
- pass the input into the function
- the condition to print out the answer is wrong so I flipped the print statements
- no need for float given number
- changed the condition in the while loop to check for while n != 0
- simplified the return statement in func to temp == origonal
- added temp = on line 34 to make sure it is being reassigned
- added int to remainder to give it a datatype
- added using namespace std to allow for std functions
- changed the name of the function call to func instead of func2
- main returns an int
- changed from n / 10 to n % 10 to get the last digit
- added an origonal value to the func to keep track of what it was in the beginning
*/