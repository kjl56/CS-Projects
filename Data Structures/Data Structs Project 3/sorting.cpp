/*
COPYRIGHT (C) 2018 Kyle Lugo (4148313) All rights reserved.
Data Structures Project III
Author.  Kyle Lugo
        kjl56@zips.uakron.edu
Version. 1.00 11.14.2018
Purpose: to analyze the runtimes of four different sorting algorithms.
*/
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <stdlib.h>

#include "heapsort.h"
#include "insertsort.h"
#include "mergesort.h"
#include "quicksort.h"

int main()
{
  //prompt user for file name
  std::cout << "Please enter the filename: ";
  std::string fileName;
  std::cin >> fileName;

  //check if file exists, if so load it. if not, print error
  std::ifstream inputFile;
  inputFile.open(fileName);
  if (inputFile)
  {
    std::cout << "Enter the number of integers to sort: ";
    int numOfInts;
    std::cin >> numOfInts;

    //make vector of ints with ints from file
    std::vector<int> inputInts;
    while (!inputFile.eof())
    {
      int tempNum;
      inputFile >> tempNum;
      if (!inputFile.fail())
      {
        inputInts.push_back(tempNum);
      }
    }

    //test heap sort on sample input file
    std::vector<int> heapTest;
    heapTest = inputInts;
    std::cout << std::endl << "vector before heap sort: ";
    for (auto i : heapTest)
    {
      std::cout << i << " ";
    }
    heapsort(heapTest);
    std::cout << std::endl << "vector after heap sort: ";
    for (auto i : heapTest)
    {
      std::cout << i << " ";
    }

    //test merge sort on sample input file
    std::vector<int> mergeTest;
    mergeTest = inputInts;
    std::cout << std::endl << "vector before merge sort: ";
    for (auto i : mergeTest)
    {
      std::cout << i << " ";
    }
    mergeSort(mergeTest);
    std::cout << std::endl << "vector after merge sort: ";
    for (auto i : mergeTest)
    {
      std::cout << i << " ";
    }

    //test quick sort (no cutoff) on sample input file
    std::vector<int> quickTest;
    quickTest = inputInts;
    std::cout << std::endl << "vector before quick sort (no cutoff): ";
    for (auto i : quickTest)
    {
      std::cout << i << " ";
    }
    quicksort(quickTest);
    std::cout << std::endl << "vector after quick sort (no cutoff): ";
    for (auto i : quickTest)
    {
      std::cout << i << " ";
    }

    //test insertion sort on sample input file
    std::vector<int> insertionTest;
    insertionTest = inputInts;
    std::cout << std::endl << "vector before insertion sort: ";
    for (auto i : insertionTest)
    {
      std::cout << i << " ";
    }
    std::vector<int>::iterator vecBegin = insertionTest.begin();
    std::vector<int>::iterator vecEnd = insertionTest.end();
    insertionSort(vecBegin, vecEnd);
    std::cout << std::endl << "vector after insertion sort: ";
    for (auto i : insertionTest)
    {
      std::cout << i << " ";
    }



    std::cout << std::endl << "runtime of algorithms for N = " << numOfInts << " items";

    //populate a vector of random ints of size N
    std::vector<int> randInts;
    // initialize random seed
    srand (time(NULL));
    for (int i = 0; i < numOfInts; ++i)
    {
      //generate secret number between 1 and N
      int iSecret = rand() % numOfInts + 1;
      //insert random number into vector
      randInts.push_back(iSecret);
    }
    //populate a vector of ascending ints of size N
    std::vector<int> ascendInts;
    for (int i = 1; i <= numOfInts; ++i)
    {
      ascendInts.push_back(i);
    }
    //populate a vector of descending ints of size N
    std::vector<int> descendInts;
    for (int i = numOfInts; i > 0; --i)
    {
      descendInts.push_back(i);
    }


    //sort copies of the vectors with heap sort for runtime analysis
    std::vector<int> heapRand = randInts;
    std::vector<int> heapAscend = ascendInts;
    std::vector<int> heapDescend = descendInts;

    std::cout << std::endl << "heap sort random: ";
    clock_t start, stop;
    start = clock ();
    heapsort(heapRand);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "heap sort ascending: ";
    start = clock ();
    heapsort(heapAscend);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "heap sort descending: ";
    start = clock ();
    heapsort(heapDescend);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    //sort copies of the vectors with merge sort for runtime analysis
    std::vector<int> mergeRand = randInts;
    std::vector<int> mergeAscend = ascendInts;
    std::vector<int> mergeDescend = descendInts;

    std::cout << std::endl << "merge sort random: ";
    start = clock ();
    mergeSort(mergeRand);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "merge sort ascending: ";
    start = clock ();
    mergeSort(mergeAscend);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "merge sort descending: ";
    start = clock ();
    mergeSort(mergeDescend);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    //sort copies of the vectors with quick sort (no cutoff) for runtime analysis
    std::vector<int> quickRand = randInts;
    std::vector<int> quickAscend = ascendInts;
    std::vector<int> quickDescend = descendInts;

    std::cout << std::endl << "quick sort (no cutoff) random: ";
    start = clock ();
    quicksort(quickRand);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "quick sort (no cutoff) ascending: ";
    start = clock ();
    quicksort(quickAscend);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "quick sort (no cutoff) descending: ";
    start = clock ();
    quicksort(quickDescend);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    //sort copies of the vectors with insertion sort for runtime analysis
    std::vector<int> insertRand = randInts;
    std::vector<int> insertAscend = ascendInts;
    std::vector<int> insertDescend = descendInts;

    std::cout << std::endl << "insertion sort ascending: ";
    vecBegin = insertAscend.begin();
    vecEnd = insertAscend.end();
    start = clock ();
    insertionSort(vecBegin, vecEnd);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "insertion sort random: ";
    vecBegin = insertRand.begin();
    vecEnd = insertRand.end();
    start = clock ();
    insertionSort(vecBegin, vecEnd);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);

    std::cout << std::endl << "insertion sort descending: ";
    vecBegin = insertDescend.begin();
    vecEnd = insertDescend.end();
    start = clock ();
    insertionSort(vecBegin, vecEnd);
    stop = clock ();
    std::cout << double(stop-start)/double(CLOCKS_PER_SEC);
  }
  else
  {
    std::cout << "That file does not exist." << std::endl;
  }
  return 0;
}
