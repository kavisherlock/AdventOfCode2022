#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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

class Valve {
  public:
    string name;
    int flowRate;
    vector<string> neighbours;

  int getPressureReleased(int minutes) {
    return flowRate * minutes;
  }
};

map<string, int> memMap;
int nCalls;

int getMaxPressure(map<string, Valve> &valves, string curValve, int minutesRemaining, vector<string> openValves) {
  if (minutesRemaining <= 1) {
    return 0;
  }
  if (minutesRemaining == 2) {
    if (find(openValves.begin(), openValves.end(), curValve) == openValves.end())
      return valves[curValve].flowRate * (minutesRemaining - 1);
    else
      return 0;
  }

  sort(openValves.begin(), openValves.end());
  string memMapKey = curValve + to_string(minutesRemaining);
  for (string v : openValves) memMapKey += v;
  if (memMap.count(memMapKey) > 0) {
    return memMap[memMapKey];
  }
  nCalls += 1;

  int maxPressure = 0;
  for (string neighbour : valves[curValve].neighbours) {
    int pressureIfWeMove = getMaxPressure(valves, neighbour, minutesRemaining - 1, openValves);
    if (maxPressure < pressureIfWeMove) {
      maxPressure = pressureIfWeMove;
    }
    if (valves[curValve].flowRate > 0 && find(openValves.begin(), openValves.end(), curValve) == openValves.end()) {
      vector<string> newOpenValves = openValves;
      newOpenValves.push_back(curValve);
      int pressureIfWeOpenAndMove = valves[curValve].flowRate * (minutesRemaining - 1) + getMaxPressure(valves, neighbour, minutesRemaining - 2, newOpenValves);
      if (maxPressure < pressureIfWeOpenAndMove) {
        maxPressure = pressureIfWeOpenAndMove;
      }
    }
  }

  memMap[memMapKey] = maxPressure;
  return maxPressure;
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

  map<string, Valve> valves;
  for (string line : lines) {
    int dividerPos = line.find("; ");
    string valePart = line.substr(0, dividerPos);
    string tunnelsPart = line.substr(dividerPos + 2);
    Valve valve;
    valve.name = valePart.substr(6, 2);
    valve.flowRate = stoi(valePart.substr(23));
    valve.neighbours = split(tunnelsPart.substr(23), ", ");
    valves[valve.name] = valve;
  }

  vector<string> openValves;
  cout << getMaxPressure(valves, "AA", 30, openValves) << endl;
  cout << nCalls << endl;
}
