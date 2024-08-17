#include <chrono>
#include <ctime>
#include <fstream>

#include "hash.h"
using namespace std::chrono;

struct Book {
  string title;
  string author;
};

int main() {
  fstream file;
  file.open("../books.txt", ios::in);

  hashTable<string, string> table;
  table.init(300000);
  Book* array = new Book[300000];
  int n = 0;
  getline(file, array[n].title, '|');
  getline(file, array[n].author);

  while (!file.eof() && getline(file, array[n].title, '|')) {
    getline(file, array[n].author);
    table.add(array[n].title, array[n].author);
    n++;
  }

  cout << endl << "Time compare: " << endl << endl;
  // test with data located at the beginning of the dataset.
  auto start = high_resolution_clock::now();
  table.searchValue("Classical Mythology");
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Data located at the beginning of the dataset: " << endl;
  cout << "Hash Table (Chaining AVL): " << duration.count()
       << " microseconds" << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    if (array[i].title == "Classical Mythology") {
      break;
    }
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);

  cout << "Linear Search: " << duration.count() << " microseconds" << endl << endl;

  // test with data located at the middle of the dataset.
  start = high_resolution_clock::now();
  table.searchValue("The Enchantress");
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Data located at the middle of the dataset: " << endl;
  cout << "Hash Table (Chaining AVL): " << duration.count()
       << " microseconds" << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    if (array[i].title == "The Enchantress") {
      break;
    }
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Linear Search: " << duration.count() << " microseconds" << endl << endl;

  // test with data located at the end of the dataset.
  start = high_resolution_clock::now();
  table.searchValue(
      "A Guided Tour of Rene Descartes' Meditations on First Philosophy with "
      "Complete Translations of the Meditations by Ronald Rubin");
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Data located at the end of the dataset: " << endl;
  cout << "Hash Table (Chaining AVL): " << duration.count()
       << " microseconds" << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    if (array[i].title ==
        "A Guided Tour of Rene Descartes' Meditations on First Philosophy with "
        "Complete Translations of the Meditations by Ronald Rubin") {
      break;
    }
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Linear Search: " << duration.count() << " microseconds" << endl << endl;

  // test with data does not exist in the dataset.
  start = high_resolution_clock::now();
  table.searchValue("Wish Me Happy");
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Data does not exist in the dataset" << endl;
  cout << "Hash Table (Chaining AVL): " << duration.count()
       << " microseconds" << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    if (array[i].title == "Wish Me Happy") {
      break;
    }
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Linear Search: " << duration.count() << " microseconds" << endl;

  delete[] array;
  file.close();
}