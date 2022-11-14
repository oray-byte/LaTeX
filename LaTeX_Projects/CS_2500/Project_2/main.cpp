/**
 * @file main.cpp
 * @author ormd3n (ormd3n@umsystem.edu)
 * @brief Main driver file for Algorithm timing
 * @version 0.1
 */

#include "algorithmManager.h"
void printErr();

int main(int argc, char* argv[])
{
	// For testing if we got enough data
	unsigned int i, runs, increment;
	string file;
	int* data;
	ifstream input;
	unsigned long long initial, max;

	// Accepting arguments to set intial, max, and increment
	if (argc == 6)
	{
		// Assigning arguments to variables
		file = argv[1];
		std::istringstream ss1(argv[2]);
		std::istringstream ss2(argv[3]);
		std::istringstream ss3(argv[4]);
		std::istringstream ss4(argv[5]);
		if (!(ss1 >> initial) || !(ss2 >> max) || !(ss3 >> increment) || !(ss4 >> runs))
		{
			printErr();
			exit(1);
		}
	}
	else
	{
		printErr();
		exit(1);
	}

	// Initialize data array
	data = new int[max];

	// Copying data from input file into data array. Data in input file must match data type of array.
	input.open(file);
	i = 0;
	while ((input >> data[i]) && (i < (max - 1)))
	{
		i++;
	}
	input.close();

	if ((i == 0))
	{
		cout << "Wrong data type" << endl;
		exit(1);
	}

	AlgorithmManager<int> am(data, initial, false);
	

	for (int i = initial; i <= max; i+= increment)
	{
		am.size = i;
		am.timeAlgorithm(QuickSort, runs);
	}

	am.exportResults("quick_sort");

	for (int i = initial; i <= max; i+= increment)
	{
		am.size = i;
		am.timeAlgorithm(MergeSort, runs);
	}

	am.exportResults("merge_sort");

	for (int i = initial; i <= max; i+= increment)
	{
		am.size = i;
		am.timeAlgorithm(HeapSort, runs);
	}

	am.exportResults("heap_sort");

	for (int i = initial; i <= max; i+= increment)
	{
		am.size = i;
		am.timeAlgorithm(MergeInsertionSort, runs);
	}

	am.exportResults("merge_insertion_sort");

	return 0;
}

void printErr()
{
	cout << ".\\program [1] [2] [3] [4] [5]" << endl;
	cout << "[1] - Input file with data to be tested on. Must be same data type as variable 'data' at compile time." << endl;
	cout << "[2] - Initial size of the array of data to be tested. Must be greater than zero and an integer." << endl;
	cout << "[3] - Max size of the array of data to be tested. This should be the number of lines in your input file, greater than zero, and an integer." << endl;
	cout << "[4] - The size of increments that will be taken when testing sorts with each input size. Must be an integer" << endl;
	cout << "[5] - The number of runs the sorting algorithms will take for each input size; "; 
	cout << "higher the value, the longer but more accurate the results will be. Must be greater than zero and an integer" << endl;
}