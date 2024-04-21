#include "hash_function.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int BinaryMidSquareHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int *arr = new int[2 * key_size];
  for (int i = 0; i < 2 * key_size; i++)
    arr[i] = 0;
  int idx = 0;
  int num = key * key;
  while (num) {
    arr[idx] = num % 2;
    num /= 2;
    idx++;
  } // into binary
  int mid = 0;
  idx = key_size - index_size / 2;
  int bin = 0;
  for (int i = 0; i < index_size; i++) {
    bin = power(2, i);
    mid += arr[idx] * bin;
    idx++;
  }
  return mid;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int DigitFoldingHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int *arr = new int[key_size];
  for (int i = 0; i < key_size; i++)
    arr[i] = 0;
  int idx = 0;
  int num = key;
  while (num) {
    arr[idx] = num % 2;
    num /= 2;
    idx++;
  } // into binary
  int sum = 0;
  for (int i = 0; i < key_size; i++)
    sum += arr[i];
  return sum;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int MultiplicationHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  double ka = key * A;
  double frac = ka - static_cast<int>(ka);
  return static_cast<int>(power(2, index_size) * frac);
  return -1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
int BinaryMidSquareHash::power(int base, int exp) {
  int n = 1;
  for (int i = 0; i < exp; i++)
    n *= base;
  return n;
}

int MultiplicationHash::power(int base, int exp) {
  int n = 1;
  for (int i = 0; i < exp; i++)
    n *= base;
  return n;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
