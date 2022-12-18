#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
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

unordered_map<string, int> memMap;
int nCalls = 0;

int getMaxPressure(
  unordered_map<string, Valve> &valves,
  string curValve,
  vector<string> prevValves,
  string curEValve,
  vector<string> prevEValves,
  int minutesRemaining,
  vector<string> openValves,
  int nOpenableValves
) {
  if (minutesRemaining <= 1 || openValves.size() >= nOpenableValves || find(prevValves.begin(), prevValves.end(), curValve) != prevValves.end() || find(prevEValves.begin(), prevEValves.end(), curEValve) != prevEValves.end()) {
    return 0;
  }

  bool canOpenCurValve = valves[curValve].flowRate > 0 && find(openValves.begin(), openValves.end(), curValve) == openValves.end();
  bool canOpenCurEValve = valves[curEValve].flowRate > 0 && find(openValves.begin(), openValves.end(), curEValve) == openValves.end();
  
  if (minutesRemaining == 2) {
    int pressure = 0;
    if (canOpenCurValve)
      pressure += valves[curValve].flowRate * (minutesRemaining - 1);
    if (canOpenCurEValve && curValve != curEValve)
      pressure += valves[curEValve].flowRate * (minutesRemaining - 1);
    
    return pressure;
  }

  string memMapKey = curValve < curEValve ? curValve + curEValve : curEValve + curValve;
  memMapKey += to_string(minutesRemaining);
  if (openValves.size() > 0) {
    sort(openValves.begin(), openValves.end());
    for (string v : openValves) memMapKey += v;
  }
  if (memMap.count(memMapKey) > 0) {
    return memMap[memMapKey];
  }

  nCalls += 1;
  if (nCalls % 1000000 == 0) cout << nCalls << endl;

  int maxPressure = 0;
  // both open our valves
  if (curValve != curEValve && canOpenCurValve && canOpenCurEValve) {
    vector<string> newOpenValves = openValves;
    newOpenValves.push_back(curValve);
    newOpenValves.push_back(curEValve);
    int pressureIfBothOpen = valves[curValve].flowRate * (minutesRemaining - 1);
    pressureIfBothOpen += valves[curEValve].flowRate * (minutesRemaining - 1);
    pressureIfBothOpen += getMaxPressure(valves, curValve, vector<string>(), curEValve, vector<string>(), minutesRemaining - 1, newOpenValves, nOpenableValves);
    if (maxPressure < pressureIfBothOpen) {
      maxPressure = pressureIfBothOpen;
    }
  }

  // one opens, other leaves
  if (canOpenCurValve) {
    vector<string> newOpenValves = openValves;
    newOpenValves.push_back(curValve);
    vector<string> newprevEValves = prevEValves;
    newprevEValves.push_back(curEValve);
    for (string eNeighbour : valves[curEValve].neighbours) {
      if (find(prevEValves.begin(), prevEValves.end(), eNeighbour) != prevEValves.end()) continue;
      int pressureIfOneOpens = valves[curValve].flowRate * (minutesRemaining - 1);
      pressureIfOneOpens += getMaxPressure(valves, curValve, vector<string>(), eNeighbour, newprevEValves, minutesRemaining - 1, newOpenValves, nOpenableValves);
      if (maxPressure < pressureIfOneOpens) {
        maxPressure = pressureIfOneOpens;
      }
    }
  }

  // one leaves, other opens
  if (canOpenCurEValve && curValve != curEValve) {
    vector<string> newOpenValves = openValves;
    newOpenValves.push_back(curEValve);
    vector<string> newprevValves = prevValves;
    newprevValves.push_back(curValve);
    for (string neighbour : valves[curValve].neighbours) {
      if (find(prevValves.begin(), prevValves.end(), neighbour) != prevValves.end()) continue;
      int pressureIfOtherOpens = valves[curEValve].flowRate * (minutesRemaining - 1);
      pressureIfOtherOpens += getMaxPressure(valves, neighbour, newprevValves, curEValve, vector<string>(), minutesRemaining - 1, newOpenValves, nOpenableValves);
      if (maxPressure < pressureIfOtherOpens) {
        maxPressure = pressureIfOtherOpens;
      }
    }
  }

  // both leave
  vector<string> newprevValves = prevValves;
  newprevValves.push_back(curValve);
  vector<string> newprevEValves = prevEValves;
  newprevEValves.push_back(curEValve);
  for (string neighbour : valves[curValve].neighbours) {
    for (string eNeighbour : valves[curEValve].neighbours) {
      if (find(prevValves.begin(), prevValves.end(), neighbour) != prevValves.end() || find(prevEValves.begin(), prevEValves.end(), eNeighbour) != prevEValves.end()) continue;
      int pressureIfWeMove = getMaxPressure(valves, neighbour, newprevValves, eNeighbour, newprevEValves, minutesRemaining - 1, openValves, nOpenableValves);
      if (maxPressure < pressureIfWeMove) {
        maxPressure = pressureIfWeMove;
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

  unordered_map<string, Valve> valves;
  int nOpenableValves = 0;
  for (string line : lines) {
    int dividerPos = line.find("; ");
    string valePart = line.substr(0, dividerPos);
    string tunnelsPart = line.substr(dividerPos + 2);
    Valve valve;
    valve.name = valePart.substr(6, 2);
    valve.flowRate = stoi(valePart.substr(23));
    if (valve.flowRate > 0) nOpenableValves += 1;
    valve.neighbours = split(tunnelsPart.substr(23), ", ");
    valves[valve.name] = valve;
  }

  vector<string> openValves;
  cout << getMaxPressure(valves, "AA", vector<string>(), "AA", vector<string>(), 26, openValves, nOpenableValves) << endl;
  cout << nCalls << endl;
}
