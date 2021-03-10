/********************************************************************//**
 * @file
 ***********************************************************************/
#include "disjointBySize.h"

DisjointSet::DisjointSet() : nodes(nullptr), size(0), sets(0) {}

DisjointSet::~DisjointSet()
{
   if (nodes) delete [] nodes;
}

// Create a universe of disjoint sets from 0 to (n-1).
// This will remove any existing relationships
void DisjointSet::makeSet(long n)
{
   // Don't do anything if we already of a large enough set
   // This may have unexpected results if the user is expecting to take 
   // advantage of the side effect of removing existing relationships
   if (n <= size) return;

   // Free up the existing array
   if (nodes) delete [] nodes;

   size = n;
   sets = n;
   nodes = new long int[size];
   for (int i = 0 ; i < size ; i++)
      nodes[i] = -1;
}

// Create a relationship between the set represented by 'first' and the set
// represented by 'second'
void DisjointSet::Union(long first, long second)
{
   int a = findSet(first);
   int b = findSet(second);
   
   if (a == b) return;

   sets--;
   if (nodes[a] < nodes[b])
   {
      nodes[a] += nodes[b];
      nodes[b] = a;
   }
   else
   {
      nodes[b] += nodes[a];
      nodes[a] = b;
   }
}

// Return the representative of the set in which 'data' belongs
long DisjointSet::findSet(long data)
{
   while (nodes[data] >= 0)
      data = nodes[data];

   return data;
}

long DisjointSet::setCount() { return sets ; }
