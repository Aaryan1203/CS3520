// This program should read any string (including spaces) from the user and print it using a character pointer
// The program is setup to use pointer offset notation to get each character of the string

// Number of bugs/errors : 8

#include <iostream> // include iostream and dont include stdio
#include <string>

using namespace std;

int main() // changed return type of void to int and removed the void parameter
{
  char s[20];
  char* cPtr; // should be a character pointer
  cout << "Enter a string: "; // Prompt for input
  cin.getline(s, 20); // Use getline to read the entire line including spaces
  cPtr = s;
  while (*cPtr != '\0') // no need for -- // dereference the pointer // changed condition from == to !=
  {
    cout << *cPtr; // dereference the pointer
    cPtr++; 
  }
  cout << "\n";
  return 0;
}
