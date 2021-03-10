/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef DISJOINTBYSIZE_H
#define DISJOINTBYSIZE_H

/********************************************************************//**
 * @class DisjointBySize
 **********************************************************************/
class DisjointSet
{
   /// The array that holds the disjoint sets
   long int *nodes;
   /// The size of the array
   long int size; 
   long int sets;

public:
   DisjointSet();

   ~DisjointSet();

   /// Allocates the array of nodes for the disjoint sets
   void makeSet(long int);

   /// Performs the union operation
   void Union(long int, long int);

   /// Returns the set that represents a particular item
   long int findSet(long int);

   /// Returns the number of disjoint sets remaining
   long int setCount();
};
#endif
