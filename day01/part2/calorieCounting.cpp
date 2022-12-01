#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  vector<int> maxCals;
  if (myfile.is_open()) {
    string lineString;
    int cummuativeCals = 0;
    while(getline(myfile, lineString)) {
      if (lineString.size() == 0) {
        if (maxCals.size() < 3) {
          maxCals.push_back(cummuativeCals);
        } else {
          vector<int>::iterator minMaxCals = min_element(maxCals.begin(), maxCals.end());
          if (*minMaxCals < cummuativeCals) {
            *minMaxCals = cummuativeCals;
          }
        }
        cummuativeCals = 0;
      } else {
        cummuativeCals += stoi(lineString);
      }
    }
  }
  myfile.close();

  cout << accumulate(maxCals.begin(), maxCals.end(), 0) << endl;
}
