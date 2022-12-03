#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int PRIORITY_A = 27;
const int PRIORITY_a = 1;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  int prioritySum = 0;
  if (myfile.is_open()) {
    string rucksackItems;
    while(getline(myfile, rucksackItems)) {
      int nItems = rucksackItems.size();
      string firstCompartment = rucksackItems.substr(0, nItems / 2);
      string secondCompartment = rucksackItems.substr(nItems / 2);
      for (char item : firstCompartment) {
        if (secondCompartment.find(item) != string::npos) {
          prioritySum += item >= 'a' ? item - 'a' + PRIORITY_a : item - 'A' + PRIORITY_A;
          break;
        }
      }
    }
  }
  myfile.close();

  cout << prioritySum << endl;
}
