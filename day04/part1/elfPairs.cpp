#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string s, string delimiter) {
  vector<string> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(s);
  return results;
}

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

  int fullyOverlappingCount = 0;
  for (string pairLine : lines) {
    vector<string> pair = split(pairLine, ",");
    vector<string> elfOneAssignment = split(pair[0], "-");
    int elfOneStart = stoi(elfOneAssignment[0]);
    int elfOneEnd = stoi(elfOneAssignment[1]);
    vector<string> elfTwoAssignment = split(pair[1], "-");
    int elfTwoStart = stoi(elfTwoAssignment[0]);
    int elfTwoEnd = stoi(elfTwoAssignment[1]);

    if ((elfOneStart >= elfTwoStart && elfOneEnd <= elfTwoEnd)
     || (elfTwoStart >= elfOneStart && elfTwoEnd <= elfOneEnd)) {
      fullyOverlappingCount += 1;
     }
  }

  cout << fullyOverlappingCount << endl;
}
