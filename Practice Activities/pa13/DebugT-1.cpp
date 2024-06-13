// Debug T-1
// Function template adds objects. The function works on any object which has '+' opertor defined.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

#include <iostream>
#include <string>
using namespace std;
template <class T>
T add(T x, T y) // missing type for y
{
   T sum = x + y; // changed type for sum
   return sum;
}
// this is not needed
// {
//    U sum;
//    sum = x + y;
//    return sum;
// }
class Person
{
   friend ostream &operator<<(ostream &, const Person &);

private:
   string lastName;
   string firstName;
   int age;

public:
   void setValues(string, string, int);
   Person operator+(Person); // capital P in Person
};

ostream &operator<<(ostream &out, const Person &per) // should have a const for the Person to match the definition 
{
   out << per.firstName << " " << per.lastName << " " << per.age << " years old" << endl; 
   return out; // return the ostream
}

void Person::setValues(string last, string first, int age)
{
   lastName = last;
   firstName = first;
   this->age = age; // use a pointer to specify the age
}

Person Person::operator+(Person p)
{
   Person temp;
   temp.lastName = "of Age";
   temp.firstName = "Sum";
   temp.age = p.age + this->age; // ensure to add this persons age instead of the temps age and assign it to the temps age
   return temp;
}

int main()
{
   int a = 7, b = 26, c;
   double d = 39.25, e = 2.01, f;
   Person g, h, i;
   g.setValues("Mitchell", "Donald", 40);
   h.setValues("Clayton", "Rita", 35);
   c = add(a, b);
   f = add(d, e);
   i = add(g, h);
   cout << c << endl;
   cout << f << endl;
   cout << i << endl;
   return 0;
}
/*
Summary of changes:
   1. Removed extra block in the template function.
   2. Changed the type for sum in the add function.
   3. Ensured operator<< returns the ostream.
   4. Added const correctness to operator<< to match the definition.
   5. Corrected logical errors in Person::operator+ to properly calculate the age.
   6. Updated setValues method to use this->age.
*/