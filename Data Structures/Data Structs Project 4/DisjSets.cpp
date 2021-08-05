//Kyle Lugo (4148313)
#include "DisjSets.h"

/**
 * Construct the disjoint sets object.
 */
DisjSets::DisjSets( int numElements ) : s( numElements, -1 )
{
}

/**
 * Union two disjoint sets.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */

void DisjSets::unionSets(int root1, int root2) {
	if (s[root1] < s[root2])
	{
    s[root1] += s[root2]; //update size of root1 tree
    s[root2] = root1;  // Make root1 new root
  }
  else
	{
    s[root2] += s[root1];  //update size of root 2
    s[root1] = root2;     // make root2 new root
	}
}


/**
 * Perform a find with path halving per exercise 8.16a from the book.
 */
int DisjSets::find( int x )
{
  if( s[ x ] < 0 ) //base case for root
    return x;
  else if (find( s[ x ] ) < 0) //base case for node with no grandparent
    return s[x];
  else
    return s[x]= find( s[ x ] );

}

//used to determine if two cells are connected
//This function will invoke the DisjSets::find( )method
bool DisjSets::isConnected(int n1, int n2)
{
  if (find(n1) == find(n2))
  {
    return true;
  }
  return false;
}
