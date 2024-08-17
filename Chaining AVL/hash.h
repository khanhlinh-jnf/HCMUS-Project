#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename K, typename V>
struct hashTable {
  struct hashNode {
    K key;
    V value;
    hashNode* left;
    hashNode* right;
  };

  int capacity;
  vector<hashNode*> table;

  void init(unsigned int hashSize);
  void release();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  hashNode* rightRotate(hashNode* y);
  hashNode* leftRotate(hashNode* y);
  hashNode* minNode(hashNode* node);
  void AVLInsert(hashNode*& root, hashNode* newNode);
  void add(K key, V value);
  int getBalance(hashNode* node);
  int getHeight(hashNode* node);
  V* searchValue(K key);
  hashNode* searchAVL(hashNode* root, K key);
  void removeKey(K key);
  hashNode* removeAVL(hashNode* root, K key);
  void NLR(hashNode* root);
  void displayTable();

};

#include "hash.cpp"