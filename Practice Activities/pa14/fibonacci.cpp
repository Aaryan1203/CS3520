// Fibonacci calculations performed in separate threads
#include <iostream>
#include <iomanip>
#include <future>
#include <ctime>
using namespace std;

// class to represent the results
class ThreadData
{
public:
    time_t startTime;    // time thread starts processing
    time_t endTime;      // time thread finishes processing
    thread::id threadId; // thread ID
}; // end class ThreadData

unsigned long long int fibonacci(unsigned int n); // function prototype
ThreadData startFibonacci(unsigned int n);        // function prototype

int main()
{
    int num1, num2, num3;
    cout << "We will be calculating the fibonacci numbers for your given three numbers and the amount of time it takes to computer it" << endl;
    cout << "Ensure all threee number are greater than 30" << endl;
    cout << "Number 1: ";
    while (cin >> num1) {
        if (num1 < 30) {
            cout << "Please enter a number greater than 30" << endl;
        } else {
            break;
        }
    }
    cout << "Number 2: ";
    while (cin >> num2) {
        if (num2 < 30) {
            cout << "Please enter a number greater than 30" << endl;
        } else {
            break;
        }
    }
    cout << "Number 3: ";
    while (cin >> num3) {
        if (num3 < 30) {
            cout << "Please enter a number greater than 30" << endl;
        } else {
            break;
        }
    }

    cout << fixed << setprecision(6);
    cout << "Calculating fibonacci( " << num1 << " ), fibonacci( " << num2 << " ) and fibonacci( " << num3 << " ) in separate threads" << endl;

    // Sequential execution
    auto startSequential = chrono::high_resolution_clock::now();
    startFibonacci(num1);
    startFibonacci(num2);
    startFibonacci(num3);
    auto endSequential = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedSequential = endSequential - startSequential;
    cout << "Sequential calculation time: " << elapsedSequential.count() << " seconds" << endl;

    // Parallel execution
    cout << "Starting threads to calculate fibonacci numbers..." << endl;
    auto startParallel = chrono::high_resolution_clock::now();
    auto futureResult1 = async(launch::async, startFibonacci, num1);
    auto futureResult2 = async(launch::async, startFibonacci, num2);
    auto futureResult3 = async(launch::async, startFibonacci, num3);

    // wait for results from each thread
    ThreadData result1 = futureResult1.get();
    ThreadData result2 = futureResult2.get();
    ThreadData result3 = futureResult3.get();
    auto endParallel = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedParallel = endParallel - startParallel;

    cout << "Parallel calculation time: " << elapsedParallel.count() << " seconds" << endl;

    cout << "Thread ID for fibonacci(" << num1 << "): " << result1.threadId << endl;
    cout << "Thread ID for fibonacci(" << num2 << "): " << result2.threadId << endl;
    cout << "Thread ID for fibonacci(" << num3 << "): " << result3.threadId << endl;

    return 0;
} // end main

// executes function fibonacci asynchronously
ThreadData startFibonacci(unsigned int n)
{
    // create a ThreadData object to store times
    ThreadData result = {0, 0};
    result.threadId = this_thread::get_id();

    result.startTime = time(nullptr); // time before calculation
    auto fibonacciValue = fibonacci(n);
    result.endTime = time(nullptr); // time after calculation

    // display fibonacci calculation result and total calculation time
    cout << "Calculation time " << n << " = "
         << difftime(result.endTime, result.startTime) / 60.0
         << " minutes\n"
         << endl;
    return result;
} // end function startFibonacci

// Recursively calculates fibonacci numbers
unsigned long long int fibonacci(unsigned int n)
{
    // base case
    if (0 == n || 1 == n)
    {
        return n;
    } // end if
    else // recursive step
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    } // end else
} // end function fibonacci
