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

  int stepIndex = -1;
  bool stepsFound = false;
  while (!stepsFound) {
    stepsFound = lines[++stepIndex][0] == 'm';
  }
  
  int nStacks = (lines[stepIndex - 2].size() + 1) / 4; // each stack required four chars in the input
  string stacks[nStacks];
  int curStackInd = stepIndex - 3;
  while (curStackInd >= 0) {
    for (int i = 0; i < nStacks; i += 1) {
      char crate = lines[curStackInd][(i * 4) + 1];
      if (crate >= 'A' && crate <= 'Z')
        stacks[i].push_back(crate);
    }
    curStackInd -= 1;
  }
  
  for (int i = stepIndex; i < lines.size(); i += 1) {
    string step = lines[i];
    vector<string> stepStuff = split(step, " ");
    int nStacksToMove = stoi(stepStuff[1]);
    int fromStack = stoi(stepStuff[3]) - 1;
    int toStack = stoi(stepStuff[5]) - 1;

    stacks[toStack] += stacks[fromStack].substr(stacks[fromStack].size() - nStacksToMove, nStacksToMove);
    for (int i = 0; i < nStacksToMove; i += 1) {
      stacks[fromStack].pop_back();
    }
  }

  for (string stack : stacks) {
    cout << stack[stack.size() - 1];
  }
  cout << endl;
}
