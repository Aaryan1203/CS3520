// Automatic dialing machine
// Delivers a sales message
/* Needs to print all possible combinations of areacode and exchangecode with the last 4 digits


Example : If areacode = 617, exchange = 424
Output : 
"I am calling to tell you to buy a subscription to Dogs Monthly Magazine!"
617-424-0001
617-424-0002
617-424-0003
...
617-424-9998
617-424-9999
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

#include<iostream> // changed % to #
#include <string> // Added string ibrary
using namespace std; // include namespace to use basic functions without needing std::

int main(){
   int digit1, digit2, digit3, digit4; // changed from char to int
   string areaCode, exchange;
   cout<< "Hello, I am a telemarketing calling making program.\n";
   cout<< "Enter a three-digit area code "; 
   cin >> areaCode; // changed to cin to allow for user input
   cout<<"Enter a three-digit exchange to call "; 
   cin >> exchange; // changed to cin to allow for user input
   cout<< "I am calling to tell you to buy a subscription to Dogs Monthly!\n";
   for(digit1 = 0; digit1 <= 9; ++digit1){ // incremented digits
        for(digit2 = 0; digit2 <=9; ++digit2){ 
            for(digit3 = 0; digit3 <=9; ++digit3) { 
                for(digit4 = 0; digit4 <=9; ++digit4) {
                    cout<< areaCode << "-" << exchange << "-" << digit1 << digit2 << digit3 << digit4 << endl;
                }
            }
        }
    }
    
   return 0;
}

/*
Changes
- Changed % to # on line 21 when including the iostream
- Added '#include <string>' so the file can recognize strings
- Instead of decrementing the digits, I incremented them
- Added the line 'using namespace std;' and got rid of the std:: before every cout call
- Replaced the cout<<areaCode and exhchange with cin >> areacode and exchange so it was actually taking in the values
- changed the datatypes for the digits from char's to int's
- got rid of Calls Completed statement as it was not in the expected output
*/