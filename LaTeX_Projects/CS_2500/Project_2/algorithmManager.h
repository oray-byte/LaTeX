/**
 * @file algorithmManager.h
 * @author ormd3n (ormd3n@umsystem.edu)
 * @brief Contrains declarations for AlgorithmManager<T> and enums
 * @version 0.1
 * @date 2022-10-25
 */

#ifndef ALGORITHM_MANAGER_H
#define ALGORITHM_MANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <sstream>

using namespace std::chrono;
using std::vector;
using std::pair;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::random_shuffle;
enum Algorithm {InsertionSort, MergeSort, HeapSort, QuickSort, MergeInsertionSort};

template <class T>
class AlgorithmManager
{
    public:
    T* data;
    // Set true in main.cpp to enable debug outputs and functionality (assertions)
    bool debug;
    // Function pointer typedef
    typedef void (AlgorithmManager<T>::*fn)();

    // Size of data array
    unsigned long long size;

    // Prints internal array
    void printArray();

    /**
     * @brief Times algorithms based on the parameters. A pointer to a static function is created
     *        based on the algorithm. After creating the pointer to the function wrapper, the average 
     *        is recorded in respective internal vectors.
     * @param algorithm States which algorithm is being tested
     * @param runs How many times algorithm will be tested at each input size 
     * @result Average times for each input size n stored in respective vectors
     */
    void timeAlgorithm(Algorithm algorithm, int runs);

    AlgorithmManager(T* data, int initialSize, bool debug = false);

    ~AlgorithmManager()  { delete[] data; data = nullptr; }

    /**
     * @brief Takes the values stored in randomResults, bestResults, and worstResults and exports them into three .csv files
     *        The vectors are then emptied and readied for the next algorithm's results.
     * 
     * @param algorithm Name of the algorithm whose results are stored. If you use same name, old results will
     *                  be overwritten.
     * @result Three .csv files with the names "random_case_${algorithm}.csv", "best_case_${algorithm}.csv", 
     *         and "worst_case_${algorithm}.csv"
     */
    void exportResults(string algorithm);

    private:
    // All three hold averaged time, double, at each input size size, int
    // Vectors instead of arrays since being able to change size of data structure easily is good for storing results
    vector<pair<int, double>> randomResults;
    vector<pair<int, double>> sortedResults;
    vector<pair<int, double>> reverseResults;
    // Average of each run to be manipulated
    unsigned long long average;
    // Function pointer
    fn func;

    /**
     * @brief Randomizes internal array data<T>[0...(size - 1)]
     * @return Internal array data<T>[0...(size - 1)] randomized
     */
    void randomizeArray();

    /**
     * @brief Sorts internal array data<T> from 0 to (size - 1)
     * @return Internal array data<T>[0...(size - 1)] sorted
     */
    void sortArray();

    /**
     * @brief Reverse sorts internal array data<T> from 0 to (size - 1)
     * @return Internal array data<T>[0...(size - 1)] reverse sorted
     */
    void reverseSortArray();

    /**
     * @brief Averages all data in the vector
     * 
     * @param toAverage The vector to average values with 
     * @return Average of type double 
     */
    double averageVector(const vector<long long> &toAverage);

    /**
     * @brief Merges data[left...middle] and data[middle+1...right]
     * 
     * @param left Beginning index of first sub-array
     * @param middle Ending index of first sub-array, middle+1 is beginning index of second sub-array
     * @param right Ending index of second sub-array
     */
    void merge(int left, int middle, int right);

    /**
     * @brief Max-heapify index
     * 
     * @param index Index to max-heapify
     * @param heapSize Remaining size of non-sorted array
     */
    void heapify(int index, int heapSize);

    /**
     * @brief Builds heap from an array
     * 
     * @param heapSize Size of remaining non-sorted array
     */
    void buildHeap(int heapSize);

    /**
     * @brief Paritions sub-array into three sections: values less than pivot, values greater than pivot, and pivot
     * 
     * @param left Starting index of sub-array
     * @param right Ending index of sub-array
     * @return int
     */
    int partition(int left, int right);

    /**
     * @brief Sorting algorithm that sorts by testing current index with previous indexes and inserting it if
     *        if the current value is less than the value it is being tested against. Best-case time is O(n),
     *        random-case time is O(n)~O(n^2), and the worst-case time is O(n^2). If debug = true, we test
     *        loop invariant with assert statements, however that increases the time it takes. Invariant is 
     *        described within the method.
     * 
     * @result Sorts data<T>[0...(size - 1)] in ascending order
     */
    void insertionSort();

    /**
     * @brief Pretty much identical to insertion sort, except only sorting a sub-array
     * 
     * @param left Starting index of sub-array
     * @param right Ending index of sub-array
     */
    void mergeInsert(int left, int right);
    
    /**
     * @brief Sorts data<T>[0...(size - 1)] by using merge sort. It is always O(nlgn) regardless of input case.
     *        If debug = true, we test loop invariant with assert statements.
     * 
     * @param left Minimum index
     * @param right Maximum index
     * 
     * @result Sorts data<T>[0...(size - 1)] in ascending order
     */
    void mergeSort(int left, int right);

    /**
     * @brief Sorts data<T>[0...size] by using heapSort
     * 
     */
    void heapSort();

    /**
     * @brief Sorts data<T>[0...size] by using quickSort
     * 
     * @param left Left index
     * @param right Right index
     */
    void quickSort(int left, int right);

    /**
     * @brief Combination of merge and insertion sort. At a hardcoded input size, in this case 43, the sub-array will be sorted 
     *        with insertion sort instead of merge sort
     * 
     * @param left Starting index of sub-array
     * @param right Ending index of sub-array
     */
    void mergeInsertionSort(int left, int right);

    /**
     * @brief Wrapper method for insertion sort. The timeAlgorithm method needs each sort to have the same amount of parameters.
     *        it is achievable using the wrapper functions. It also handles how many times the sort function will run and which 
     *        case is being tested.
     * 
     * @param runs Amount of runs the sort function will do at size size
     * @param sort Which test case we are sorting (random, sorted, reverse-sorted)
     */
    void insertionSortWrapper();

    /**
     * @brief Wrapper method for merge sort. The timeAlgorithm method needs each sort to have the same amount of parameters.
     *        it is achievable using the wrapper functions. It also handles how many times the sort function will run and which 
     *        case is being tested.
     * 
     * @param runs Amount of runs the sort function will do at size size
     * @param sort Which test case we are sorting (random, sorted, reverse-sorted)
     */
    void mergeSortWrapper();

    /**
     * @brief Wrapper method for heap sort. The timeAlgorithm method needs each sort to have the same amount of parameters.
     *        it is achievable using the wrapper functions. It also handles how many times the sort function will run and which 
     *        case is being tested.
     * 
     * @param runs Amount of runs the sort function will do at size size
     * @param sort Which test case we are sorting (random, sorted, reverse-sorted)
     */
    void heapSortWrapper();

    /**
     * @brief Wrapper method for quick sort. The timeAlgorithm method needs each sort to have the same amount of parameters.
     *        it is achievable using the wrapper functions. It also handles how many times the sort function will run and which 
     *        case is being tested.
     * 
     * @param runs Amount of runs the sort function will do at size size
     * @param sort Which test case we are sorting (random, sorted, reverse-sorted)
     */
    void quickSortWrapper();

    /**
     * @brief Wrapper method for merge-insertion sort. The timeAlgorithm method needs each sort to have the same amount of parameters.
     *        it is achievable using the wrapper functions. It also handles how many times the sort function will run and which 
     *        case is being tested.
     * 
     * @param runs Amount of runs the sort function will do at size size
     * @param sort Which test case we are sorting (random, sorted, reverse-sorted)
     */
    void mergeInsertionSortWrapper();

};

#include "algorithmManager.hpp"

#endif