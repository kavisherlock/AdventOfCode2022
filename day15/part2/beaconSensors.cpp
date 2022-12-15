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
  for (string line : lines) {
    Sensor sensor(line);
    sensors.push_back(sensor);
  }

  long maxD = 4000000;
  for (int i = 0; i < maxD + 1; i += 1) {
    for (int j = 0; j < maxD + 1; j += 1) {
      bool withinReach = false;
      for (Sensor sensor : sensors) {
        int manDis = sensor.getManDistance(i, j);
        if (manDis <= sensor.beaconDistance) {
          long verticalDistance = sensor.y - j;
          long horizontalDistance = sensor.x - i > 0 ? sensor.x - i : i - sensor.x;
          if (sensor.beaconDistance - horizontalDistance + verticalDistance >= 0) j += sensor.beaconDistance - horizontalDistance + verticalDistance;
          withinReach = true;
          break;
        }
      }
      if (!withinReach) {
        cout << i << " " << j << endl;
        cout << i * maxD + j << endl;
        return 0;
      }
    }
  }
}
