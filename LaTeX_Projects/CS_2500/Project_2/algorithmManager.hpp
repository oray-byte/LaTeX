/**
 * @file algorithmManager.hpp
 * @author ormd3n (ormd3n@umsystem.edu)
 * @brief Contains definitions for algorithmManager.h
 * @version 0.1
 * @date 2022-10-25
 */

#include "algorithmManager.h"

template <class T>
AlgorithmManager<T>::AlgorithmManager(T* data, int initialSize, bool debug)
{
    this->size = initialSize;
    this->debug = debug;
    this->data = data;
    this->average = 0;
}

template <class T>
void AlgorithmManager<T>::timeAlgorithm(Algorithm algorithm, int runs)
{
    // Pointer to function in memory. Since functions are in an instance of a class, the functions MUST be static.
    vector<long long> toAverage;
    int i;

    // Based on algorithm input, assigns func to corresponding algorithm
    // They are all wrappers so they have the number of parameters
    switch (algorithm)
    {
        case InsertionSort:
            this->func = &AlgorithmManager<T>::insertionSortWrapper;
            break;
        case MergeSort:
            this->func = &AlgorithmManager<T>::mergeSortWrapper;
            break;
        case HeapSort:
            this->func = &AlgorithmManager<T>::heapSortWrapper;
            break;
        case QuickSort:
            this->func = &AlgorithmManager<T>::quickSortWrapper;
            break;
        case MergeInsertionSort:
            this->func = &AlgorithmManager<T>::mergeInsertionSortWrapper;
            break;
    }

    // Handles worst case for func
    cout << "\nRandom case at n = " << size << endl;
    for (i = 0; i < runs; i++)
    {
        randomizeArray();
        auto start = high_resolution_clock::now();
        (this->*func)();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        if (debug)
        {
            cout << "The sort function sorted the array: ";
            sorted = std::is_sorted(data, data + size);
            assert(sorted);
            (sorted ? cout << "True\n" : cout << "False\n");
            cout << endl;
        }
        toAverage.push_back(duration.count());
    }

    average = averageVector(toAverage);
    toAverage.clear();
    randomResults.push_back(pair<int, double>(size, (average / 1.00)));
    cout << "Average (ns): " << (average / 1.00) << endl;;
    average = 0;

    // Handles best case for func
    cout << "\nSorted case at n = " << size << endl;
    for (i = 0; i < runs; i++)
    {
        sortArray();
        auto start = high_resolution_clock::now();
        (this->*func)();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        if (debug)
        {
            cout << "The sort function sorted the array: ";
            sorted = std::is_sorted(data, data + size);
            assert(sorted);
            (sorted ? cout << "True\n" : cout << "False\n");
            cout << endl;
        }
        toAverage.push_back(duration.count());
    }

    average = averageVector(toAverage);
    toAverage.clear();
    sortedResults.push_back(pair<int, double>(size, (average / 1.00)));
    cout << "Average (ns): " << (average / 1.00) << endl;
    average = 0;

    // // Handles worst case for func
    cout << "\nReversely-sorted case at n = " << size << endl;
    for (i = 0; i < runs; i++)
    {
        reverseSortArray();
        auto start = high_resolution_clock::now();
        (this->*func)();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        if (debug)
        {
            cout << "The sort function sorted the array: ";
            sorted = std::is_sorted(data, data + size);
            assert(sorted);
            (sorted ? cout << "True\n" : cout << "False\n");
            cout << endl;
        }
        toAverage.push_back(duration.count());
    }

    average = averageVector(toAverage);
    toAverage.clear();
    reverseResults.push_back(pair<int, double>(size, (average / 1.00)));
    cout << "Average (ns): " << (average / 1.00) << endl;
    average = 0;
}

template <class T>
void AlgorithmManager<T>::exportResults(string algorithm)
{
    // All three vectors must be filled
    if ((randomResults.size() == 0) || (sortedResults.size() == 0) || (reverseResults.size() == 0))
    {
        return;
    }
    ofstream output;
    int i;

    // Push results from randomResults to "random_case.csv" to be manipulated in Excel later
    output.open("random_case_" + algorithm + ".csv");
    output << "n,time (ns)" << endl;
    for (i = 0; i < randomResults.size(); i++)
    {
        output << randomResults[i].first << "," << randomResults[i].second << endl;
    }
    output.close();
    randomResults.clear();

    // Push results from bestResults to "best_case.csv" to be manipulated in Excel later
    output.open("sorted_case_" + algorithm + ".csv");
    output << "n,time (ns)" << endl;
    for (i = 0; i < sortedResults.size(); i++)
    {
        output << sortedResults[i].first << "," << sortedResults[i].second << endl;
    }
    output.close();
    sortedResults.clear();
    // Push results from worstResults to "worst_case.csv" to be manipulated in Excel later
    output.open("reverse_case_" + algorithm + ".csv");
    output << "n,time (ns)" << endl;
    for (int i = 0; i < reverseResults.size(); i++)
    {
        output << reverseResults[i].first << "," << reverseResults[i].second << endl;
    }
    output.close();
}

template <class T>
void AlgorithmManager<T>::printArray()
{
    for (int i = 0; i < size; i++)
    {
        cout << i << ": " << data[i] << endl;
    }
    cout << endl;
}

template <class T>
void AlgorithmManager<T>::randomizeArray()
{
    srand(time(NULL));

    // Shuffles data[0...size] and size increments by inputted(?) value
    random_shuffle(data, (data + size));
}

template <class T>
void AlgorithmManager<T>::sortArray()
{
    randomizeArray();
    
    // Utilizing built-in sort function to sort vector in ascending order
    std::sort(data, (data + size));
}

template <class T>
void AlgorithmManager<T>::reverseSortArray()
{
    // Randomize vector and sort in ascending order
    sortArray();

    // Utilizing built-in reverse function to reverse the sorted vector 
    std::reverse(data, (data + size));
}

template <class T>
double AlgorithmManager<T>::averageVector(const vector<long long> &toAverage)
{
    double sum = 0;
    double average;
    for (int i = 0; i < toAverage.size(); i++)
    {
        sum += toAverage[i];
    }

    average = (sum / toAverage.size());

    return average;
}

template <class T>
void AlgorithmManager<T>::merge(int left, int middle, int right)
{
    if ((right - left) == 0)
    {
        return;
    }
    int i, j, k, leftLength, rightLength;

    // Size of left and right arrays
    leftLength = (middle - left) + 1;
    rightLength = right - middle;

    // Dynamically allocated because I like pointers
    T* leftArr = new T[leftLength];
    T* rightArr = new T[rightLength];

    // Filling left and right arrays
    for (i = 0; i < leftLength; i++)
    {
        leftArr[i] = data[left + i];
    }

    for (j = 0; j < rightLength; j++)
    {
        rightArr[j] = data[middle + 1 + j];
    }
    i = 0;
    j = 0;
    k = left;

    // Merge left and right array into main array
    while ((i < leftLength) && (j < rightLength))
    {
        if (leftArr[i] <= rightArr[j])
        {
            data[k] = leftArr[i];
            i++;
        }
        else
        {
            data[k] = rightArr[j];
            j++;
        }
        k++;

        if (debug)
        {
            for (int n = left; n < (right - left); n++)
            {
                for (int l = i; l < leftLength; l++)
                {
                    assert(data[n] < data[l]);
                }

                for (int l = j; j < rightLength; l++)
                {
                    assert(data[n] < data[l]);
                }
            }
        }
    }

    // Extra elements in left array
    while (i < leftLength)
    {
        data[k] = leftArr[i];
        k++;
        i++;
    }

    while (j < rightLength)
    {
        data[k] = rightArr[j];
        k++;
        j++;
    }

    delete[] leftArr;
    delete[] rightArr;

    if (debug)
    {
        assert(std::is_sorted(data+left, data+right));
    }
}

template <class T>
void AlgorithmManager<T>::heapify(int index, int heapsize)
{
    if (size == 0)
    {
        return;
    }
    int largest = index;
    int leftChild = (2 * index) + 1;
    int rightChild = (2 * index) + 2;

    if ((leftChild <= heapsize) && (data[leftChild] > data[largest]))
    {
        largest = leftChild;
    }

    if ((rightChild <= heapsize) && (data[rightChild] > data[largest]))
    {
        largest = rightChild;
    }

    if (index != largest)
    {
        swap(data[index], data[largest]);
        heapify(largest, heapsize);
    }
}

template <class T>
void AlgorithmManager<T>::buildHeap(int heapSize)
{
    if (size == 0)
    {
        return;
    }
    for (int i = floor(size / 2) - 1; i >= 0; i--)
    {
        heapify(i, heapSize);
    }
}

template <class T>
int AlgorithmManager<T>::partition(int left, int right) 
{
    if ((right - left) == 0)
    {
        return;
    }

    T x = data[right];
    int i = left - 1;
    for (int j = left; j < right; j++) 
    {
        if (data[j] <= x) 
        {
            i++;
            swap(data[i], data[j]);
            if (debug)
            {
                for (int n = left; n <= i; n++)
                {
                    assert(data[n] <= x);
                }
            }
        }
        if (debug)
        {
            for (int n = i + 1; n < j; n++)
            {
                assert(data[n] > x)
            }
        }
    }

    swap(data[i + 1], data[right]);
    return i + 1;
}

template <class T>
void AlgorithmManager<T>::insertionSort()
{
    // Guard condition
    int j = 1;
    // Must have one element
    if (size == 0)
    {
        return;
    }

    if (debug)
    {
        // Invariant initialization (A[1] is sorted)
        assert(data[0] <= data[0]);
    }

    for (; j < size; j++)
    {
        if (debug)
        {
            // Pre loop invariant maintenance (A[1..j-1] is sorted)
            for (int i = 0; i < (j - 1); i++)
            {
                assert(data[i] <= data[(i + 1)]);
            }
        }

        T key = data[j];
        int i = j - 1;

        while ((i >= 0) && (data[i] > key))
        {
            data[i + 1] = data[i];
            i = i - 1;
        }
        data[i + 1] = key;

        if (debug)
        {
            // Post loop invariant maintenance (A[1..j] is sorted)
            for (int i = 0; i < j; i++)
            {
                assert(data[i] <= data[(i + 1)]);
            }
        }
    }

    if (debug)
    {
        // Invariant termination (A[1..n] is sorted)
        for (int i = 0; i < size - 1; i++)
        {
            assert((data[i] <= data[i + 1]) && !(j < size));
        }
    }
}

template <class T>
void AlgorithmManager<T>::mergeSort(int left, int right)
{
    if (size == 0)
    {
        return;
    }

    if (left < right)
    {
        int middle = left + ((right - left)/2);
        mergeSort(left, middle);
        mergeSort((middle + 1), right);
        merge(left, middle, right);
    }

    return;
}

template <class T>
void AlgorithmManager<T>::heapSort()
{
    if (size == 0)
    {
        return;
    }

    int heapSize = size - 1;
    T temp;
    buildHeap(heapSize);

    for (int i = (size - 1); i >= 1; i--)
    {
        temp = data[i];
        data[i] = data[0];
        data[0] = temp;
        heapSize--;
        heapify(0, heapSize);
    }
    if (debug)
    {
        assert(std::is_sorted(data, data + size));
    }
}

template <class T>
void AlgorithmManager<T>::quickSort(int left, int right)
{
    if (size == 0)
    {
        return;
    }

    if (left < right)
    {
        int q = partition(left, right);
        quickSort(left, q - 1);
        quickSort(q + 1, right);
    }

    if (debug)
    {
        assert(std::is_sorted(data + left, data + right));
    }
}

template <class T>
void AlgorithmManager<T>::mergeInsertionSort(int left, int right)
{
    if (size == 0)
    {
        return;
    }

    if ((right - left) > 43)
    {
        int middle = left + ((right - left)/2);
        mergeSort(left, middle);
        mergeSort((middle + 1), right);
        merge(left, middle, right);
    }
    else
    {
        mergeInsert(left, right);
    }

    if (debug)
    {
        assert(std::is_sorted(data + left, data + right));
    }
}

template <class T>
void AlgorithmManager<T>::mergeInsert(int left, int right)
{
    // Guard condition
    int j = left + 1;
    // Must have one element
    if ((right - left) == 0)
    {
        return;
    }

    for (; j < (right - left); j++)
    {

        T key = data[j];
        int i = j - 1;

        while ((i >= 0) && (data[i] > key))
        {
            data[i + 1] = data[i];
            i = i - 1;
        }
        data[i + 1] = key;

        if (debug)
        {
            assert(std::is_sorted(data + left, data + j));
        }
    }

    if (debug)
    {
        // Invariant termination (A[1..n] is sorted)
        for (int i = left; i < right - 1; i++)
        {
            assert((data[i] <= data[i + 1]) && !(j < size));
        }
    }
}

template <class T>
void AlgorithmManager<T>::insertionSortWrapper()
{
    insertionSort();
}

template <class T>
void AlgorithmManager<T>::mergeSortWrapper()
{
    mergeSort(0, size);
}

template <class T>
void AlgorithmManager<T>::heapSortWrapper()
{
    heapSort();
}

template <class T>
void AlgorithmManager<T>::quickSortWrapper()
{
    quickSort(0, (size - 1));
}

template <class T>
void AlgorithmManager<T>::mergeInsertionSortWrapper()
{
    mergeInsertionSort(0, size);
}