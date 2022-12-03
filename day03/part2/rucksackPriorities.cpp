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
  string firstElf = "";
  string secondElf = "";
  string thirdElf = "";
  if (myfile.is_open()) {
    string rucksackItems;
    while(getline(myfile, rucksackItems)) {
      if (firstElf == "") {
        firstElf = rucksackItems;
      } else if (secondElf == "") {
        secondElf = rucksackItems;
      } else {
        thirdElf = rucksackItems;
        for (char item : thirdElf) {
          if (firstElf.find(item) != string::npos && secondElf.find(item) != string::npos) {
            prioritySum += item >= 'a' ? item - 'a' + PRIORITY_a : item - 'A' + PRIORITY_A;
            break;
          }
        }

        firstElf = "";
        secondElf = "";
      }
    }
  }
  myfile.close();

  cout << prioritySum << endl;
}
