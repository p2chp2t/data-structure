#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

sortAlg::sortAlg() {
  arr_size = 0;
  arr = new int[100];  // Each test case will be less than 100 values
  temp = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
  string answer;
  for (int i = 0; i < arr_size - 1; i++)
    answer += to_string(arr[i]) + " ";
  answer += to_string(arr[arr_size - 1]);
  fout << answer << endl;
}

void sortAlg::insertionSort(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int ins;
  int j;
  for (int i = 0; i < arr_size - 1; i++) {
    ins = arr[i + 1];
    for (j = i; j >= 0; j--) {
      if (arr[j] > ins)
        arr[j + 1] = arr[j];
      else
        break;
    }
    arr[j + 1] = ins;
    printArray(fout); // DO NOT ERASE THIS LINE
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int mid = (left + right) / 2;
  int i = left, j = mid + 1;
  int k = left;
  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
      count++; // drop occurs
    }
  }
  while (i <= mid) { // left side of array remains
    temp[k++] = arr[i++];
  }
  while (j <= right) { // right side of array remains
    temp[k++] = arr[j++];
  }
  for (int i = left; i <= right; i++) {
    arr[i] = temp[i];
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (left < right) {
    int mid = (left + right) / 2;
    mergeSort(fout, left, mid, count);
    mergeSort(fout, mid + 1, right, count);
    merge(left, right, count);
    printArray(fout); // DO NOT ERASE THIS LINE
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
