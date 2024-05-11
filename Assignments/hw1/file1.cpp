/* Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'


*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

#include <iostream>
using namespace std;

int main() {
  // initialized limit with 10, and the even_product and odd_product with 1
  int limit = 10, even_product = 1, odd_product = 1, sum; 

  cout << "The value of limit is " << limit << endl;

  for (int i = 1; i <= limit; ++i) { // start the loop at 1
    if (i % 2 == 1) {
      odd_product *= i;
    } else {
      even_product *= i; // swapped even_product and odd_product
    }
  }
  sum = even_product + odd_product;
  cout << "The Sum = " << sum << "\n";

  for (char c = 'Z'; c >= 'A'; c -= 2) {
    cout << c << " "; // changed 'i' to 'c'
  }
  cout << endl;

  return 0;
}

/*
- Limit is initialized to 10 as the problem expects the limit to be 10
- even_product and odd_product are initialized to 1 because anything multiplied by 0 is 0
- Change i to c on line 36 because the defined variable is c not i
- Started the for loop at 1 instead of 0 because if the first iteration is 0, then 
  since it is being multiplied by other values, the total product will be 0
- Swapped the odd_product and even_product variables 
- Defined char c in the loop instead of outside the loop as that is good practice
*/