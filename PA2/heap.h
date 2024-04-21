#pragma once
#include <iostream>
#include <string>
using namespace std;

class MaxHeap
{

public:
  MaxHeap();

  int heap_size;

  void maxHeapProp(/*your heap array*/);
  void insertKey(string sen);
  void deleteMax();
  string printHeap();
  /////////////////////////////////////////////////////////
  //////  TODO: Add Public members if required ///////////
  void swap(int idx1, int idx2)
  {
    char temp = harr[idx1];
    harr[idx1] = harr[idx2];
    harr[idx2] = temp;
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  string harr; // pointer to heap elements
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
