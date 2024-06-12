
#include <iostream>
#include <cstring>
#include <memory>
using namespace std;
class MyString
{
    unique_ptr<char[]> str;

public:
    MyString() : str{new char[1]}
    { // Default Constructor
        str[0] = '\0';
    };
    MyString(char *val)
    { // Constructor with 1 arguments
        str = unique_ptr<char[]>(new char(strlen(val) + 1));
        strcpy(str.get(), val);
        cout << "The given string is: " << str.get() << endl;
    }
    MyString(const MyString &source)
    { // Copy Constructor
        str = unique_ptr<char[]>(new char(strlen(source.str.get()) + 1));
        strcpy(str.get(), source.str.get());
    }
    MyString(MyString &&source) noexcept : str(move(source.str))
    { // Move Constructor
    }
    ~MyString() = default; // Destructor
};
int main(void)
{
    cout << "Start!" << endl;
    MyString a;
    MyString b{(char *)"Hello"};
    MyString c{a};
    MyString d{MyString{(char *)"World"}};
    cout << "Bye" << endl;
}

/*
Changes to the constructor:
    In the default constructr, I used unique_ptr to allocate a single character initialized to the null character
    In the parameterized constructor, I used unique_ptr to allocate the necessary memory, and strcpy is used to copy the input string
Copy Constructor:
    I used unique_ptr to allocate the necessary memory, and strcpy is used to copy the input string
Move Constructor:
    I used the default move constructor as it will automatically handle the move operation
Changes to the destructor:
    I used the default destructor as it will automatically handle memory deallocation
*/