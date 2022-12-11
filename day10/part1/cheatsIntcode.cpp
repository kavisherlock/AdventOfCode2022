#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  int nCycles = 0;
  int xVal = 1;
  int totalStrength = 0;
  for (string line : lines) {
    nCycles += 1;
    if ((nCycles - 20) % 40 == 0 && nCycles <= 220) {
      totalStrength += nCycles * xVal;
    }

    string command = line.substr(0, 4);
    if (command == "noop") {
      continue;
    }

    nCycles += 1;
    if ((nCycles - 20) % 40 == 0 && nCycles <= 220) {
      totalStrength += nCycles * xVal;
    }
    xVal += stoi(line.substr(5));
  }

  cout << totalStrength << endl;
}
