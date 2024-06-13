// Debug T-2
// Function template finds biggest of two or three objects. The function works on any data type which has greater than operator defined.

#include <iostream>
#include <string>
using namespace std;
template <class T>
void findBiggest(T a, T b, T c) // b should be of type T
{
   T large = a;
   if (b > large)
      large = b;
   if (c > large) // changed from < to >
      large = c;
   cout << "The largest of " << a << " " << b << " " << c << " is " << large << endl; // changes to large to print the largest value
}

template <class T>
void findBiggest(T a, T b)
{
   T large = a;
   if (b > large) // changes from == to > to properly compare the two values
      large = b;
   cout << "The larger of " << a << " " << b << " is " << large << endl; // change from large to larger
}
class BankAccount
{
   friend ostream &operator<<(ostream &, const BankAccount &);

private:
   string name;
   int amount;

public:
   BankAccount(const string &name, const int); // add the name field to the constructor
   bool operator>(const BankAccount &);
};

BankAccount::BankAccount(const string &name, const int amount)
{
   this->name = name; // added this->name to assign the name to the object
   this->amount = amount; // added this->amount to assign the amount to the object
}
ostream &operator<<(ostream &out, const BankAccount &bh) // added const before Bank Account
{
   out << "Name " << bh.name << " Amount: " << bh.amount << endl; // ensure to call name and amount on bh
   return out;
}
bool BankAccount::operator>(const BankAccount &bh)
{
   bool flag = false; // changed == to = to assign the value to flag
   if (amount > bh.amount)
      flag = true;
   return flag;
}
int main()
{
   BankAccount bAA("A", 800);
   BankAccount bAB("B", 120);
   BankAccount bAC("C", 500);
   findBiggest(bAA, bAB);
   findBiggest(bAB, bAC);
   findBiggest(bAC, bAA);
   findBiggest(bAA, bAB, bAC);
   return 0;
}

/*
   Summary of changes:
   1. Fixed comparison operators in findBiggest functions.
   2. Corrected template function signatures and comparison logic.
   3. Added necessary constructors and member assignments in BankAccount.
   4. Ensured const correctness in operator overloads.
   5. Simplified and corrected comparison logic in BankAccount::operator>.
*/
