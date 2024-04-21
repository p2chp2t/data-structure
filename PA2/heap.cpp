#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

MaxHeap::MaxHeap()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  heap_size = 0;
  harr = " ";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string MaxHeap::printHeap()
{
  string answer = "";
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  for (int i = 1; i <= heap_size; i++)
  {
    answer += harr[i];
    answer += " ";
  }

  answer.pop_back();
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return answer;
}

void MaxHeap::insertKey(string sen)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (sen.find('"') != string::npos)
    sen = sen.substr(1, sen.length() - 2);
  for (int j = 0; j < sen.length(); j++)
  {
    harr += sen[j];
    heap_size++;
    // up-heap bubbling
    int idx = heap_size;
    while (idx > 1 && harr[idx] < harr[idx / 2])
    {
      swap(idx, idx / 2);
      idx /= 2;
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::deleteMax()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  harr[1] = harr[heap_size];
  heap_size--;
  maxHeapProp();
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::maxHeapProp(/*your heap array*/)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here   /////////////
  for (int i = heap_size / 2; i >= 1; i--)
  {
    int idx = 1;
    while (idx * 2 <= heap_size)
    {
      int child = idx * 2;
      if (child < heap_size && harr[child] > harr[child + 1])
      {
        child++;
      }
      if (harr[idx] > harr[child])
      {
        swap(idx, child);
        idx = child;
      }
      else
        break;
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}