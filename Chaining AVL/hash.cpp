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
  hashNode* newNode = new hashNode;
  newNode->key = key;
  newNode->value = value;
  newNode->left = nullptr;
  newNode->right = nullptr;

  if (table[index] == nullptr) {
    table[index] = newNode;
  } else {
    AVLInsert(table[index], newNode);
  }
}

template <typename K, typename V>
void hashTable<K, V>::AVLInsert(hashNode*& root, hashNode* newNode) {
  if (root == nullptr) {
    root = newNode;
    return;
  }

  if (newNode->key < root->key) {
    AVLInsert(root->left, newNode);
  } else if (newNode->key > root->key) {
    AVLInsert(root->right, newNode);
  } else {
    root->value = newNode->value;
    delete newNode;
    return;
  }

  int balance = getBalance(root);

  if (balance > 1 && newNode->key < root->left->key) {
    root = rightRotate(root);
  } else if (balance < -1 && newNode->key > root->right->key) {
    root = leftRotate(root);
  } else if (balance > 1 && newNode->key > root->left->key) {
    root->left = leftRotate(root->left);
    root = rightRotate(root);
  } else if (balance < -1 && newNode->key < root->right->key) {
    root->right = rightRotate(root->right);
    root = leftRotate(root);
  }
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::rightRotate(hashNode* y) {
  hashNode* x = y->left;
  hashNode* T2 = x->right;

  x->right = y;
  y->left = T2;

  return x;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::leftRotate(hashNode* x) {
  hashNode* y = x->right;
  hashNode* T2 = y->left;

  y->left = x;
  x->right = T2;

  return y;
}

template <typename K, typename V>
int hashTable<K, V>::getHeight(hashNode* node) {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) > getHeight(node->right)
             ? getHeight(node->left) + 1
             : getHeight(node->right) + 1;
}

template <typename K, typename V>
int hashTable<K, V>::getBalance(hashNode* node) {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::minNode(hashNode* node) {
  hashNode* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  hashNode* current = table[index];
  if (current == nullptr) {
    return nullptr;
  }
  hashNode* result = searchAVL(current, key);
  return result == nullptr ? nullptr : &result->value;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::searchAVL(hashNode* root,
                                                               K key) {
  if (root == nullptr || root->key == key) return root;

  if (root->key < key) return searchAVL(root->right, key);

  return searchAVL(root->left, key);
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  if (table[index] == nullptr) {
    return;
  }
  table[index] = removeAVL(table[index], key);
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::removeAVL(hashNode* root,
                                                               K key) {
  if (root == nullptr) {
    return root;
  }

  if (key < root->key) {
    root->left = removeAVL(root->left, key);
  } else if (key > root->key) {
    root->right = removeAVL(root->right, key);
  } else {
    if ((root->left == nullptr) || (root->right == nullptr)) {
      hashNode* temp = root->left ? root->left : root->right;

      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else {
        *root = *temp;
      }
      delete temp;
    } else {
      hashNode* temp = minNode(root->right);
      root->key = temp->key;
      root->value = temp->value;
      root->right = removeAVL(root->right, temp->key);
    }
  }

  if (root == nullptr) {
    return root;
  }

  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
  }

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
  }

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

template <typename K, typename V>
void hashTable<K, V>::NLR(hashNode* root) {
  if (root != nullptr) {
    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
  }
}

template <typename K, typename V>
void hashTable<K, V>::displayTable() {
  for (int i = 0; i < capacity; i++) {
    cout << i << ": ";
    if (table[i] != nullptr) {
      NLR(table[i]);
    }
    cout << endl;
  }
}