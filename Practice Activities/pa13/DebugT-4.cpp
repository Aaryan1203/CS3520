// Debug T-5
/* Calculator class uses template class to perform arithmetic operations on different types of data.
 *  It also has function to determine which value is greater which return a boolean type.
 */

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

#include <iostream>

using namespace std;
// class to perform various operations on two variables of type T
template <class T>
class Calculator
{
private:
    T num1;
    T num2;

public:
    Calculator(T n1, T n2);
    T add();
    T subtract();
    T multiply();
    T divide();
    bool isgreater();
};

template <class T>
Calculator<T>::Calculator(T n1, T n2) // changed type of n2 to T instead of int
{
    num1 = n1;
    num2 = n2;
}

template <class T>
T Calculator<T>::add() // missing return type
{
    return num1 + num2;
}

template <class T>
T Calculator<T>::subtract() // missing return type
{
    return num1 - num2;
}

template <class T>
T Calculator<T>::multiply() // removed parameters are they are a part of the class
{
    return num1 * num2; // changed from n1 and n2 to num1 and num2
}

template <class T>
T Calculator<T>::divide()
{
    return num1 / num2; // changed % to dicide
}

template <class T>
bool Calculator<T>::isgreater() // return type should be bool
{
    if (num1 > num2)
        return true;
    else
        return false;
}

int main()
{
    Calculator<int> calc(10, 4); // int operations
    cout << calc.add() << endl;
    cout << calc.subtract() << endl;
    cout << calc.multiply() << endl;
    cout << calc.divide() << endl;
    cout << std::boolalpha << calc.isgreater() << endl;

    Calculator<double> calc2(10.234, 4.235); // double operations
    cout << calc2.add() << endl;
    cout << calc2.subtract() << endl;
    cout << calc2.multiply() << endl;
    cout << calc2.divide() << endl;
    cout << std::boolalpha << calc2.isgreater() << endl;

    // made 1 a string
    Calculator<string> calc3("Hello", "1"); // string operations
    cout << calc3.add() << endl;
    cout << std::boolalpha << calc3.isgreater() << endl;
    return 0;
}

/*
Summary of changes:
1. Changed type of n2 in the constructor to T.
2. Ensured all function definitions have the correct return type and removed unnecessary parameters.
3. Corrected arithmetic operations to use the correct operators.
4. Added return statements for all functions.
6. Ensured the isgreater() function returns a boolean type.
7. Fixed string initialization for 1 to be "1".
*/