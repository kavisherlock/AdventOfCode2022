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
  char pixels[240];
  pixels[0] = '#';
  for (string line : lines) {
    pixels[nCycles] = ((nCycles % 40) - xVal >= -1 && (nCycles % 40) - xVal <= 1) ? '#' : '.';
    nCycles += 1;
    string command = line.substr(0, 4);
    if (command == "noop") {
      continue;
    }

    pixels[nCycles] = ((nCycles % 40) - xVal >= -1 && (nCycles % 40) - xVal <= 1) ? '#' : '.';
    nCycles += 1;
    xVal += stoi(line.substr(5));
  }

  for (int i = 0; i < 6; i += 1) {
    for (int j = 0; j < 40; j += 1) {
      cout << pixels[i * 40 + j];
    }
    cout << endl;
  }
}
