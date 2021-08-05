#ifndef DISJ_SETS_H
#define DISJ_SETS_H

// DisjSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS*********************
// void union( root1, root2 ) --> Merge two sets
// int find( x )              --> Return set containing x
// ******************ERRORS********************************
// No error checking is performed

#include <vector>
using namespace std;

/**
 * Disjoint set class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */
class DisjSets
{
  public:
    explicit DisjSets( int numElements );
    void unionSets( int root1, int root2 );
    int find( int x );  // you will write code per problem 8.16a in our book
    bool isConnected(int n1, int n2); //write code for it

  private:
    vector<int> s;
};

#endif
