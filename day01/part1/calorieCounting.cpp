#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  int maxCals = 0;
  if (myfile.is_open()) {
    string lineString;
    int cummuativeCals = 0;
    while(getline(myfile, lineString)) {
      if (lineString.size() == 0) {
        if (maxCals < cummuativeCals) {
          maxCals = cummuativeCals;
        }
        cummuativeCals = 0;
      } else {
        cummuativeCals += stoi(lineString);
      }
    }
  }
  myfile.close();

  cout << maxCals << endl;
}
