// This program includes a struct called car that is used to store information
// about a given car The program should ask the user for information about their
// car and initialize a car structure with the given information The program
// should also print the information using a pointer to the initialized struct
// The information printed using the struct and the pointer should be the same


#include <iostream>
#include <string>
using namespace std; // added to allow for std functions
struct car
{
     string name; // changed the type of name to a string
     int modelYear;
     float speed;
};

int main(void)
{
     // defined the variables to be more descriptive
     string name;
     int modelYear;
     float speed;

     car c; // got rid of the word struct
     car *cPtr = &c;

     cout << "What is your favorite car's name: ";
     cin >> name;
     c.name = name; // made sure to change the cars name to name

     cout << "When was it launched : ";
     cin >> modelYear; // changed from cout to cin
     c.modelYear = modelYear;

     cout << "How much speed does it give : ";
     cin >> speed; // changed form << to >>
     c.speed = speed;

     cout << "Car's name is " << c.name << ", and should be the same as " << cPtr->name
          << ".\n";

     cout << "Car's model year is " << c.modelYear << ", and should be the same as " // changed from car.modelYear to c.modelYear
          << (*cPtr).modelYear << ".\n";
     cout << "Car's speed is " << c.speed << ", and should be the same as "
          << cPtr->speed << ".\n";
}

/*
- When defining c, don't need the keyword struct
- changed the variables of n, a, and w to be more descriptive and replaced them everywhere
- when reading the modelyear, changed from cout to cin
- when reading the speed from the user, changed the << to >>
- added c.name instead of name on line 30 to ensure we are changing the name of the car
- added using namespace std to allow for functions from std
- changed from car.modelYear to c.modelYear on line 43
- changed the datatype of name to a string
- got the values from the pointer using two different notations. first was cpty-> (fieldname) and the other was 
  (*cPtr).(fieldname). 
*/