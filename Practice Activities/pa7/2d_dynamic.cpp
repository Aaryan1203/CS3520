// This program allocated memory for an NxM integer array dynamicaly
// The program then prints the 2D array in a matrix form using a combination of * and [] operators
// Note: You can't use ** or [][] for printing the values (use a combination of * and [] only.

// Number of bugs/errors : 6

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int N = 3, M = 5;
	int i, j;
	// changed from sizeof(int) to sizeof(int *) because we are allocating memory for an array of pointers, not an array of integers
	int **d_array = (int **)malloc(N * sizeof(int *)); // Allocating memory for 2D array (N rows)
	for (i = 0; i < N; i++) // changed comma to a semicolon
		d_array[i] = (int *)malloc(M * sizeof(int *)); // Allocating memory for each row with M columns)
	// Initializing 2D array using [ ][ ] notation
	printf("Initializing array values!\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			// changed period to a semicolon
			// changed d_array + i + j to d_array[i] + j
			*(d_array[i] + j) = i + j; 
		}
	}
	// Accessing 2D array using a combination of * and [] notation
	printf("\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++) // j < M instead of N
		{
			cout << *(d_array[i] + j);
		}
		cout << "\n";
	}

	// Deallocating 2D array
	for (i = 0; i < N; i++)
		free(d_array[i]); // changed from d_array + i to d_array[i]
	free(d_array);
}

/*
- changed from sizeof(int) to sizeof(int *) because we are allocating memory for an array of pointers, not an array of integers
- on line 17, changed the comma to a semicolon after the i < N
- changed period to a semicolon
- changed d_array + i + j to d_array[i] + j to properly access the 2d array
- changed from j < N to j < M to properly iterate through the loop
- on line 43, changed from d_array + i to d_array[i] so we deallocate space for each row instead of the entire array at once
*/

