#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int MIN_X = 200;
const int MAX_X = 800;
const int MIN_Y = 0;
const int MAX_Y = 162;

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

pair<int, int> getCoordinatePair(string pairString) {
  return make_pair(stoi(pairString.substr(0, 3)), stoi(pairString.substr(4)));
}

void printCave(char cave[MAX_X - MIN_X + 1][MAX_Y + 1]) {
  for (int j = 0; j < MAX_Y + 1; j += 1) {
    for (int i = 0; i < MAX_X - MIN_X + 1; i += 1) {
      cout << cave[i][j];
    }
    cout << endl;
  }
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

  char cave[MAX_X - MIN_X + 1][MAX_Y + 1];
  for (int i = 0; i < MAX_X - MIN_X + 1; i += 1) {
    for (int j = 0; j < MAX_Y + 1; j += 1) {
      cave[i][j] = '.';
      if (j == MAX_Y) {
        cave[i][j] = '#';
      }
    }
  }

  for (string line : lines) {
    vector<string> rockEnds = split(line, " -> ");
    for (int i = 0; i < rockEnds.size() - 1; i += 1) {
      pair<int, int> end1 = getCoordinatePair(rockEnds[i]);
      pair<int, int> end2 = getCoordinatePair(rockEnds[i + 1]);
      if (end1.first == end2.first) {
        if (end1.second <= end2.second) {
          for (int y = end1.second; y <= end2.second; y += 1) {
            cave[end1.first - MIN_X][y] = '#';
          }
        } else {
          for (int y = end2.second; y <= end1.second; y += 1) {
            cave[end1.first - MIN_X][y] = '#';
          }
        }
      } else {
        if (end1.first <= end2.first) {
          for (int x = end1.first; x <= end2.first; x += 1) {
            cave[x - MIN_X][end1.second] = '#';
          }
        } else {
          for (int x = end2.first; x <= end1.first; x += 1) {
            cave[x - MIN_X][end1.second] = '#';
          }
        }
      }
    }
  }

  int nSand = 0;
  pair<int, int> curSand = make_pair(500 - MIN_X, 0);
  while(curSand.second < MAX_Y) {
    if (cave[curSand.first][curSand.second + 1] == '.') {
      curSand.second += 1;
    } else if (cave[curSand.first - 1][curSand.second + 1] == '.') {
      curSand.first -= 1;
      curSand.second += 1;
    } else if (cave[curSand.first + 1][curSand.second + 1] == '.') {
      curSand.first += 1;
      curSand.second += 1;
    } else {
      nSand += 1;
      cave[curSand.first][curSand.second] = 'o';
      if (curSand.first == 500 - MIN_X && curSand.second == 0) {
        break;
      }
      curSand = make_pair(500 - MIN_X, 0);
    }
  }

  cout << nSand << endl;
}
