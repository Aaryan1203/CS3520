// The goal of this debug execrice is to understand the concept of object slicing.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

// Expected output -
// Name: tesla model Year: 2019
// Name: Hyundai model Year: 2020 Mileage: 23
// Name: Ford model Year: 2012 Miles driven: 20000
// Name: Ford model Year: 2017 Miles driven: 10000

#include <iostream>

using namespace std;

// capatalized c in car as it is a class name
class Car
{
protected: // changed from private to protected to ensure subclasses can access the variables
    string name;
    int modelYear;
    void assign(const Car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
    }

public:
    Car(const string &n, const int my) : name(n), modelYear(my) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << endl;
    }

    virtual const Car &operator=(const Car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
        return *this;
    }
};

// capatalized s in sedan as it is a class name
class Sedan : public Car
{
private:
    int mileage;

public:
    Sedan(const string &n, const int my, const int m) : Car(n, my), mileage(m) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << " Mileage: " << mileage << endl;
    }
};

// capatalized s in suv as it is a class name
class Suv : public Car
{
    int miles;

public:
    // call the car constructor with the name and model year to ensure the variables are initialized
    Suv(const string &n, const int my, const int m) : Car(n, my), miles(m) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << " Miles driven: " << miles << endl;
    }

    virtual const Suv &operator=(const Car c)
    {
        if (const Suv *b = dynamic_cast<const Suv *>(&c))
        {
            assign(*b);
        }
        return *this;
    }

protected:
    void assign(const Suv &c)
    {
        Car::assign(c);
        miles = c.miles;
    }
};

// this casts all the cars to a car object and then prints the car object which is not what we want
// void printCarInfo(const Car c)
// {
//     c.print();
// }

int main()
{
    Car tesla = Car("tesla", 2019);
    Sedan hyundai = Sedan("Hyundai", 2020, 23);
    Suv ford = Suv("Ford", 2012, 20000);

    // call the print method on each car sperately so it calls its own print method
    tesla.print();
    hyundai.print();

    // changed from Car to Suv to ensure the correct = operator is called
    Suv &ref = ford;
    ref.print();
    Suv ford2 = Suv("Ford", 2017, 10000);
    ref = ford2;
    ref.print();
    return 0;
}

/*
    Summary of changes:
    1. Changed the access specifier of the variables in the Car class from private to protected to allow subclasses to access the variables
    2. Added a call to the Car constructor in the Suv constructor to ensure the variables are initialized
    3. Changed the print method in the Suv class to print the correct information
    4. Changed the assignment operator in the Suv class to correctly assign the values
    5. Removed the printCarInfo function as it was not needed
    6. Changed the type of ref to Suv to ensure the correct = operator is called
*/