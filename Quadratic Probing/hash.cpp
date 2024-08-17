#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(hashSize, nullptr);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; i++) {
    if (table[i] != nullptr) {
      delete table[i];
      table[i] = nullptr;
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
  unsigned int hashVal = index;
  unsigned int i = 1;
  hashNode* newNode = new hashNode{key, value};

  while (true) {
    if (table[hashVal] == nullptr) {
      table[hashVal] = newNode;
      break;
    } else {
      hashVal = (index + i * i) % capacity;
      ++i;
      if (i > capacity) {
        cout << "Table is full. Rehashing..." << endl;
        rehash();
        break;
      }
    }
  }
}

template <typename K, typename V>
void hashTable<K, V>::rehash() {
  vector<hashNode*> oldTable = table;
  table = vector<hashNode*>(capacity * 2, nullptr);
  capacity *= 2;

  for (int i = 0; i < oldTable.size(); i++) {
    if (oldTable[i] != nullptr) {
      add(oldTable[i]->key, oldTable[i]->value);
      delete oldTable[i];
    }
  }
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  unsigned int hashVal = index;
  unsigned int i = 1;

  while (true) {
    if (table[hashVal] == nullptr) {
      return nullptr;
    } else if (table[hashVal]->key == key) {
      return &table[hashVal]->value;
    } else {
      hashVal = (index + i * i) % capacity;
      ++i;
      if (i > capacity) {
        return nullptr;
      }
    }
  }
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  unsigned int hashVal = index;
  unsigned int i = 1;

  while (true) {
    if (table[hashVal] == nullptr) {
      break;
    } else if (table[hashVal]->key == key) {
      delete table[hashVal];
      table[hashVal] = nullptr;
      break;
    } else {
      hashVal = (index + i * i) % capacity;
      ++i;
      if (i > capacity) {
        break;
      }
    }
  }
}

template <typename K, typename V>
void hashTable<K, V>::displayTable() {
  for (int i = 0; i < capacity; i++) {
    if (table[i] != nullptr) {
      cout << "Index: " << i << " Key: " << table[i]->key
           << " Value: " << table[i]->value << endl;
    }
  }
}