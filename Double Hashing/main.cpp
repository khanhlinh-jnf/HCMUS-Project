#include "hash.h"

int main() {
  hashTable<string, string> h;
  h.init(10);
  h.add("one direction", "1d");
  h.add("selena gomez", "sg");
  h.add("justin bieber", "jb");
  h.add("taylor swift", "ts");
  h.add("ariana grande", "ag");
  h.add("shawn mendes", "sm");
  h.add("ed sheeran", "es");
  h.displayTable();
  cout << "-----" << endl;
  h.removeKey("selena gomez");
  h.displayTable();
  string* search = h.searchValue("taylor swift");
  if (search != nullptr) {
    cout << "Value found: " << *search << endl;
  } else {
    cout << "Value not found" << endl;
  }
  h.release();

  return 0;
}

