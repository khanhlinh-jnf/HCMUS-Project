#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

template <typename K, typename V>
struct hashTable {
  
  struct hashNode {
    K key;
    V value;
  };

  int capacity;
  vector<hashNode*> table;

  void init(unsigned int hashSize);
  void release();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  void add(K key, V value);
  void rehash();
  V* searchValue(K key);
  void removeKey(K key);
  void displayTable();
};

#include "hash.cpp"