// File: project6.tar            Instructor: Dr. Don Roberts
// Class: CS 215                 Date assigned: Nov 9, 2015
// Assignment: MP6               Date completed: nov 23, 2015
// Programmer: Simon Owens      

#include <iostream>
#include <fstream>
#include "binary_tree.h"

using namespace std;


int main() 
{
  //Header for the user
  cout << "-----------------------------------------------------------" <<endl;
  cout <<"Hello, I've been expecting you... " << endl;
  cout << "This is a test for a Treap(self balancing tree)" << endl << endl;

  srand(time(0));
  cout << "Tree 1: 1000 inserts" << endl;
  Binary_Tree<int> tree;
  //loop through 1000 elements
  for(int i = 0; i<1000; i++)
    {
      int j =i;
 
      tree.insert(j);
    }
  //check to make sure size is same as number inserted
  int size = tree.size();
  int height = tree.height();
  cout << "Height: " << height << endl;
  cout << "Size: " << size << endl << endl;
  
  cout << "Tree 2: 10000000 inserts" << endl;
  Binary_Tree<int> tree2;
  //inserts another list and checks its height..10000000 elements this time yolo
  for(int i = 0; i <10000000; i++)
    {
      int j = i;
      tree2.insert(j);
      
    } 
  size = tree2.size();
  height = tree2.height();
  cout << "Height: " << height << endl;
  cout << "Size: " << size << endl;
  
   cout << "-----------------------------------------------------------" <<endl;
  
  return 0;
}
