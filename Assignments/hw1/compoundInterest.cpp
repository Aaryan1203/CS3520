// Fig. 5.6: fig05_06.cpp
// Compound interest calculations with for.
#include <iostream>
#include <iomanip>
#include <cmath> // standard math library
using namespace std;

// This program calculates the compound interest of an investment over the years from 1626 - 2024
// It calculates the total for different interest rates between 2 and 10% each year and
// then compares it to the S&P500 and NASDAQ exchange
int main()
{
    double amount, sp500_amount, nasdaq_amount; // amount on deposit at end of 398 years
    double principal = 11.0; // initial amount before interest
    double sp500_rate = 10.17; // interest rate for the S&P500
    double nasdaq_rate = 10.4; // interest rate for NASDAQ
    int years = 398; // number of years between 1626 and 2024

    // display headers
    cout << "Interest Rate" << setw( 25 ) << "Amount in 2024" << endl;

    // set floating-point number format
    cout << fixed << setprecision( 2 );

   // calculate amount on deposit for each of interest rates
   for (double interestRate = 2; interestRate <= 10; interestRate += 0.5) {
      // calculate new amount for specified interest rate after 398 years
      amount = principal * pow( 1.0 + (interestRate / 100.0), years );

      // display the year and the amount
      cout << setw( 4 ) << interestRate << setw( 30 ) << amount << endl;
   } 

    // calulate amount for S&P500
    sp500_amount = principal * pow(1.0 + (sp500_rate / 100.0), years);
    cout << "S&P500 Returns: " << sp500_amount << endl;

    // calculate amount for the NASDAQ
    nasdaq_amount = principal * pow(1.0 + (nasdaq_rate / 100.0), years);
    cout << "NASDAQ Returns: " << nasdaq_amount << endl;
}

/*
If they had invested the money at an interest rate of 5% or above, it would
have been worth more than the $860 million that it was sold for. 
If they were to invest in the S&P500 or the NASDAQ, they would make
much more than just $860 million. 
*/

/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
