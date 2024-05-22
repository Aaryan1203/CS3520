// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.


#include <iostream>
using namespace std;
void display(int Matrix[3][3], int size); // changed type of matrix to int 

int main(void)
{
  const int size = 3; // added const to ensure it is a fixed size
  int Matrix[size][size]; // the size just needs to be size not size + 1
  cout << "Enter 9 elements of the matrix:" << endl; // changed from cin to cout
  for (int i = 0; i < size; i++) // added int in front of i
  {
    for (int j = 0; j < size; j++) // defined int j inside the loop
    {
      cin >> Matrix[i][j]; // swapped i and j
    }
  }
  display(Matrix, 3); // no need for &
  return 0;
}

void display(int Matrix[3][3], int size) //changed type of size from float to int
{
  for (int i = 0; i < size; i++) // changed comma to semicolon
  {
    for (int j = 0; j < size; j++) // changed from i++ to j++
    {
      cout << Matrix[i][j] << ", ";
    }
    cout << endl; // added semi color
  }
}

/*
- size of the matrix just needs to be size, not size + 1
- defined int j inside the for loop instead of outside it for good practice
- changed type of size from float to int in the function definition of display
- no need for & when calling display as arrays are automatically passed by their reference
- in the for loop on line 28, added a semicolon after size
- added semi colon on line 34
- in the funciton decleraiton of display, changed type of matrix to int form double
- added int in form of i on line 15
- swapped i and j on line 19 because they were flipped
- line 14 changed from cin to cout
- line 30 chagned from i++ to j++
- added the const keyword to the size variable to make sure it has a fixed size
*/