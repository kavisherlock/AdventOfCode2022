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

  // Find grid size
  int maxX = 0;
  int minX = 0;
  int maxY = 0;
  int minY = 0;
  int curX = 0;
  int curY = 0;
  for (string line : lines) {
    char direction = line[0];
    int distance = stoi(line.substr(2));
    if (direction == 'U') {
      curY -= distance;
    } else if (direction == 'D') {
      curY += distance;
    } else if (direction == 'R') {
      curX += distance;
    } else if (direction == 'L') {
      curX -= distance;
    }

    if (maxX < curX) {
      maxX = curX;
    }
    if (minX > curX) {
      minX = curX;
    }
    if (maxY < curY) {
      maxY = curY;
    }
    if (minY > curY) {
      minY = curY;
    }
  }
  cout << minX << " " << maxX << " " << minY << " " << maxY << endl;

  bool hasTVisited[maxX - minX + 1][maxY - minY + 1];
  for (int i = 0; i < maxX - minX + 1; i += 1) {
    for (int j = 0; j < maxY - minY + 1; j++) {
      hasTVisited[i][j] = false;
    }
  }

  int curHX = 0 - minX;
  int curHY = 0 - minY;
  int curTX = 0 - minX;
  int curTY = 0 - minY;
  for (string line : lines) {
    char direction = line[0];
    int distance = stoi(line.substr(2));
    for (int i = 0; i < distance; i += 1) {
      hasTVisited[curTX][curTY] = true;
      if (direction == 'U') {
        curHY -= 1;
      } else if (direction == 'D') {
        curHY += 1;
      } else if (direction == 'R') {
        curHX += 1;
      } else if (direction == 'L') {
        curHX -= 1;
      }

      if (curHX == curTX) {
        if (curTY - curHY > 1) {
          curTY -= 1;
        } else if (curTY - curHY < -1) {
          curTY += 1;
        }
      } else if (curHY == curTY) {
        if (curTX - curHX > 1) {
          curTX -= 1;
        } else if (curTX - curHX < -1) {
          curTX += 1;
        }
      } else {
        if (curTY - curHY > 1) {
          curTY -= 1;
          curTX = curHX;
        } else if (curTY - curHY < -1) {
          curTY += 1;
          curTX = curHX;
        } else if (curTX - curHX > 1) {
          curTX -= 1;
          curTY = curHY;
        } else if (curTX - curHX < -1) {
          curTX += 1;
          curTY = curHY;
        }
      }
    }
  }

  int nTVisited = 0;
  for (int i = 0; i < maxX - minX + 1; i += 1) {
    for (int j = 0; j < maxY - minY + 1; j++) {
      if (hasTVisited[i][j])
        nTVisited += 1;
    }
  }
  cout << nTVisited << endl;
}
