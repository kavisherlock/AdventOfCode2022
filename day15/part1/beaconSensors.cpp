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

class Sensor {
  public: 
    long x;
    long y;
    long bx;
    long by;
    long beaconDistance;

    Sensor() {};

    Sensor (string inputLine) {
      vector<string> inputs = split(inputLine.substr(10), ": closest beacon is at ");
      vector<string> sensor = split(inputs[0].substr(2), ", y=");
      x = stol(sensor[0]);
      y = stol(sensor[1]);
      vector<string> beacon = split(inputs[1].substr(2), ", y=");
      bx = stol(beacon[0]);
      by = stol(beacon[1]);
      beaconDistance = (x - bx > 0 ? x - bx : bx - x) + (y - by > 0 ? y - by : by - y);
    }

    long getManDistance(int dx, int dy) {
      return (x - dx > 0 ? x - dx : dx - x) + (y - dy > 0 ? y - dy : dy - y);
    }
};

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

  vector<Sensor> sensors;
  int minX = 0;
  int maxX = 0;
  for (string line : lines) {
    Sensor sensor(line);
    if (sensor.x - sensor.beaconDistance < minX) minX = sensor.x - sensor.beaconDistance;
    if (sensor.x + sensor.beaconDistance > maxX) maxX = sensor.x + sensor.beaconDistance;
    if (sensor.bx < minX) minX = sensor.bx;
    if (sensor.bx > maxX) maxX = sensor.bx;
    sensors.push_back(sensor);
  }

  long testRowInd = 2000000;
  char testRow[maxX - minX + 1];
  for (int i = 0; i < maxX - minX + 1; i += 1) {
    testRow[i] = '.';
  }
  for (Sensor sensor : sensors) {
    if (sensor.by == testRowInd) {
      testRow[sensor.bx - minX] = 'B';
    }
    long distanceFromRow = sensor.getManDistance(sensor.x, testRowInd);
    if (sensor.beaconDistance < distanceFromRow) {
      continue;
    }
    long horizontalDistance = sensor.beaconDistance - distanceFromRow;
    for (int i = sensor.x - horizontalDistance; i <= sensor.x + horizontalDistance; i += 1) {
      if (testRow[i - minX] != 'B') testRow[i - minX] = '#';
    }
  }

  int nNoBeaconPoints = 0;
  for (int i = 0; i < maxX - minX + 1; i += 1) {
    if (testRow[i] == '#') nNoBeaconPoints += 1;
  }
  cout << nNoBeaconPoints << endl;
}
