#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int N_KNOTS = 10;

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

  bool hasT9Visited[maxX - minX + 1][maxY - minY + 1];
  for (int i = 0; i < maxX - minX + 1; i += 1) {
    for (int j = 0; j < maxY - minY + 1; j++) {
      hasT9Visited[i][j] = false;
    }
  }

  int curKnotsX[N_KNOTS];
  int curKnotsY[N_KNOTS];
  for (int i = 0; i < N_KNOTS; i += 1) {
    curKnotsX[i] = 0 - minX;
    curKnotsY[i] = 0 - minY;
  }

  for (string line : lines) {
    char direction = line[0];
    int distance = stoi(line.substr(2));
    for (int i = 0; i < distance; i += 1) {
      if (direction == 'U') {
        curKnotsY[0] -= 1;
      } else if (direction == 'D') {
        curKnotsY[0] += 1;
      } else if (direction == 'R') {
        curKnotsX[0] += 1;
      } else if (direction == 'L') {
        curKnotsX[0] -= 1;
      }

      for (int k = 1; k < N_KNOTS; k += 1) {
        hasT9Visited[curKnotsX[N_KNOTS - 1]][curKnotsY[N_KNOTS - 1]] = true;
        if (curKnotsX[k - 1] == curKnotsX[k]) {
          if (curKnotsY[k] - curKnotsY[k - 1] > 1) {
            curKnotsY[k] -= 1;
          } else if (curKnotsY[k] - curKnotsY[k - 1] < -1) {
            curKnotsY[k] += 1;
          }
        } else if (curKnotsY[k - 1] == curKnotsY[k]) {
          if (curKnotsX[k] - curKnotsX[k - 1] > 1) {
            curKnotsX[k] -= 1;
          } else if (curKnotsX[k] - curKnotsX[k - 1] < -1) {
            curKnotsX[k] += 1;
          }
        } else {
          if (curKnotsX[k] - curKnotsX[k - 1] > 1 || curKnotsX[k] - curKnotsX[k - 1] < -1) {
            curKnotsX[k] += curKnotsX[k] - curKnotsX[k - 1] > 1 ? -1 : 1;
            curKnotsY[k] += curKnotsY[k] - curKnotsY[k - 1] > 0 ? -1 : 1;
          } else if (curKnotsY[k] - curKnotsY[k - 1] > 1 || curKnotsY[k] - curKnotsY[k - 1] < -1) {
            curKnotsY[k] += curKnotsY[k] - curKnotsY[k - 1] > 1 ? -1 : 1;
            curKnotsX[k] += curKnotsX[k] - curKnotsX[k - 1] > 0 ? -1 : 1;
          }
        }
      }
    }
  }

  int nTVisited = 0;
  for (int i = 0; i < maxX - minX + 1; i += 1) {
    for (int j = 0; j < maxY - minY + 1; j++) {
      if (hasT9Visited[i][j])
        nTVisited += 1;
    }
  }
  cout << nTVisited << endl;
}
