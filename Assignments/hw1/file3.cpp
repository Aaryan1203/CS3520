
#include <iostream>
using namespace std; // include namespace to use basic functions without needing std::

int main(void) {
  int num;
  bool factor_found = false; // initialized to false

  cout << "Enter Number:\n";
  cin >> num;

  if (num < 0) { // changed from == to <
    cout << num << " is negative\n";
    return 0;
  }

  if (num == 0 || num == 1) { // changed from && to ||
    cout << num << " is not prime or composite\n";
    return 0;
  }

  for (int i = 2; i < num; i++) { // loop starts at 2 and incremented i instead of decrementing it
    if (num % i == 0) {
      factor_found = true;
      break;
    }
  }

  if (factor_found) {
    
    cout << num << " is a composite number\n";
  } else {
    
   cout << num << " is a prime number\n";
  }
}

/*
Changes
- Added `using namespace std;`
- changed the condition from num == 0 to num < 0 when checking if it is negative
- Changed the && to || on line 17 when checking if it is a prime or composite number
- On line 22 change it from i-- to i++ so the loop actually increments through the values
- factor_found should be initilized to false
- The for loop should start at 2 since we are already considering the case when the number is 0 or 1
*/