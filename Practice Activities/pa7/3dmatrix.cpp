// Program to read 3-dimensional matrix and display the elements as N^3 matrix
// TODO
// take the SIZE of the matrix as input from the user
// initize matrix using update_3d method (see comments below)
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
// display cannot use nested loops

#include <iostream>
using namespace std;
// #define SIZE 7 // Change this to be an input from the user instead

void update_3d(double*** Matrix_3d, int size);
void display_1d(const double*** Matrix_3d, int size);
int main(void)
{
	int size;
	// prompt the user to initialize the matrix accordingly
	cout << "Please enter a size for the matrix: ";
	cin >> size;

	// allocating memory for the 3d matrix
    double*** Matrix_3d = new double**[size];
    for (int i = 0; i < size; i++) {
        Matrix_3d[i] = new double*[size];
        for (int j = 0; j < size; j++) {
            Matrix_3d[i][j] = new double[size];
        }
    }

	// initialize the array to non-zero values (use scanf or random numbers generator)
	update_3d(Matrix_3d, size);
	// display the values
	display_1d((const double***)Matrix_3d, size);

	// freeing allocated memory
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            delete[] Matrix_3d[i][j];
        }
        delete[] Matrix_3d[i];
    }
    delete[] Matrix_3d;

	return 0;
}

void update_3d(double*** matrix, int size)
{
	// initializing the 3d matrix with random values from 1 - 9
	cout << "Entering N^3 elements of the matrix:" << endl;
	int i = 0;
	for (; i < size; i++)
	{
		int j = 0;
		for (; j < size; j++)
		{
			int k = 0;
			for (; k < size; k++)
			{
				matrix[i][j][k] = 1 + rand() % (9);
			}
		}
	}
}

// update as needed. 1 'for' loop only with 1 iterator to print all values with addresses
// must not be able to update the array.
// Share any observations.
void display_1d(const double*** matrix, int size) {
    for (int i = 0; i < size * size * size; i++) {
        // Calculate the indices for the 3D array
        int x = i / (size * size);
        int y = (i / size) % size;
        int z = i % size;
        cout << "Address: " << &matrix[x][y][z] << ", Value: " << matrix[x][y][z] << endl;
    }
}

// I noticed that when acessing the value of a matrix, using array notation
// works the same way as dereferencing the matrix