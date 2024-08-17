#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(hashSize, nullptr);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; i++) {
    hashNode* current = table[i];
    while (current != nullptr) {
      hashNode* temp = current;
      current = current->next;
      delete temp;
    }
  }
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(int key) {
  return key % capacity;
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(string key) {
  unsigned int hash = 0;
  int p = 31;
  for (int i = 0; i < key.length(); i++) {
    hash += static_cast<unsigned int>(key[i]) *
            static_cast<unsigned int>(pow(p, i));
  }
  hash %= static_cast<unsigned int>(pow(10, 9) + 9);
  return hash % capacity;
}

template <typename K, typename V>
void hashTable<K, V>::add(K key, V value) {
  unsigned int index = hashFunction(key);
  hashNode* newNode = new hashNode{key, value, nullptr};
  if (table[index] == nullptr) {
    table[index] = newNode;
  } else {
    hashNode* current = table[index];
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  hashNode* current = table[index];
  while (current != nullptr) {
    if (current->key == key) {
      return &current->value;
    }
    current = current->next;
  }
  return nullptr;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  hashNode* current = table[index];
  hashNode* prev = nullptr;
  while (current != nullptr) {
    if (current->key == key) {
      if (prev == nullptr) {
        table[index] = current->next;
      } else {
        prev->next = current->next;
      }
      delete current;
      return;
    }
    prev = current;
    current = current->next;
  }
}

template <typename K, typename V>
void hashTable<K, V>::displayTable() {
  for (int i = 0; i < capacity; i++) {
    cout << i << ": ";
    hashNode* current = table[i];
    while (current != nullptr) {
      cout << current->key << " ";
      current = current->next;
    }
    cout << endl;
  }
}