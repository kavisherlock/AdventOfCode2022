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
    unordered_map<string, int> distanceToValves;

  int getPressureReleased(int minutes) {
    return flowRate * minutes;
  }
};

unordered_map<string, int> memMap;
int nCalls = 0;

int getMaxPressure(unordered_map<string, Valve> &valves, vector<string> &openableValves, string curValve, int minutesRemaining, vector<string> openValves) {
  if (minutesRemaining <= 1) {
    return 0;
  }
  if (openValves.size() >= openableValves.size()) {
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
  for (string valveToOpen : openableValves) {
    if (valveToOpen == curValve || find(openValves.begin(), openValves.end(), valveToOpen) != openValves.end()) {
      continue;
    }
    vector<string> newOpenValves = openValves;
    newOpenValves.push_back(valveToOpen);
    int timeRemaining = minutesRemaining - valves[curValve].distanceToValves[valveToOpen] - 1;
    if (timeRemaining <= 1) {
      continue;
    }
    int pressure =  timeRemaining * valves[valveToOpen].flowRate;
    pressure += getMaxPressure(valves, openableValves, valveToOpen, timeRemaining, newOpenValves);
    if (pressure > maxPressure) {
      maxPressure = pressure;
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
  vector<string> openableValves;
  for (string line : lines) {
    int dividerPos = line.find("; ");
    string valePart = line.substr(0, dividerPos);
    string tunnelsPart = line.substr(dividerPos + 2);
    Valve valve;
    valve.name = valePart.substr(6, 2);
    valve.flowRate = stoi(valePart.substr(23));
    if (valve.flowRate > 0) openableValves.push_back(valve.name);
    valve.neighbours = split(tunnelsPart.substr(23), ", ");
    valves[valve.name] = valve;
  }

  int nOpenableValves = openableValves.size();
  vector<string> valvesFrom = openableValves;
  valvesFrom.push_back("AA");
  for (string valveFrom : valvesFrom) {
    int valvesFound = valves[valveFrom].distanceToValves.size() + 1;
    if (valveFrom == "AA") valvesFound -= 1;
    int distanceTravelled = 0;
    vector<string> curValves = {valveFrom};
    while (valvesFound < nOpenableValves) {
      distanceTravelled += 1;
      vector<string> newCurValves;
      for (string curValve : curValves) {
        for (string neighbour : valves[curValve].neighbours) {
          newCurValves.push_back(neighbour);
          if (
            valveFrom != neighbour 
            && valves[neighbour].flowRate > 0
            && valves[valveFrom].distanceToValves.count(neighbour) == 0
          ) {
            valvesFound += 1;
            valves[valveFrom].distanceToValves[neighbour] = distanceTravelled;
            valves[neighbour].distanceToValves[valveFrom] = distanceTravelled;
          }
        }
      }
      curValves = newCurValves;
    }
  }

  vector<string> openValves;
  cout << getMaxPressure(valves, openableValves, "AA", 30, openValves) << endl;
  cout << nCalls << endl;
}

