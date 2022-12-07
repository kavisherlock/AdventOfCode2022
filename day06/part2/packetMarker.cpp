#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int MARKER_COUNT = 14;

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

  int charCount[26];
  for (int i = 0; i < 26; i += 1) {
    charCount[i] = 0;
  }

  string datastream = lines[0];
  for (int i = 0; i < MARKER_COUNT - 1; i += 1) {
    charCount[datastream[i] - 'a'] += 1;
  }

  int marker = 0;
  for (int i = MARKER_COUNT - 1; i < datastream.size(); i += 1) {
    charCount[datastream[i] - 'a'] += 1;
    bool markerFound = true;
    for (int j = i - MARKER_COUNT + 1; j <= i; j += 1) {
      if (charCount[datastream[j] - 'a'] > 1) {
        markerFound = false;
        break; 
      }
    }
    if (markerFound) {
      marker = i + 1;
      break;
    }
    charCount[datastream[i - MARKER_COUNT + 1] - 'a'] -= 1;
  }

  cout << marker << endl;
}
