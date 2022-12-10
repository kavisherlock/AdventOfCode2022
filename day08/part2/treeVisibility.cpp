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

  int nRows = lines.size();
  int nCols = lines[0].size();

  int forest[nRows][nCols];
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      forest[i][j] = lines[i][j] - '0';
    }
  }

  int maxScore = 0;
  for (int i = 1; i < nRows - 1; i += 1) {
    for (int j = 1; j < nCols - 1; j += 1) {
      int treesAbove = 0;
      for (int k = j - 1; k >= 0; k -= 1) {
        treesAbove += 1;
        if (forest[i][k] >= forest[i][j]) {
          break;
        }
      }

      int treesBelow = 0;
      for (int k = j + 1; k < nCols; k += 1) {
        treesBelow += 1;
        if (forest[i][k] >= forest[i][j]) {
          break;
        }
      }

      int treesLeft = 0;
      for (int k = i - 1; k >= 0; k -= 1) {
        treesLeft += 1;
        if (forest[k][j] >= forest[i][j]) {
          break;
        }
      }

      int treesRight = 0;
      for (int k = i + 1; k < nRows; k += 1) {
        treesRight += 1;
        if (forest[k][j] >= forest[i][j]) {
          break;
        }
      }

      int score = treesAbove * treesBelow * treesLeft * treesRight;
      if (score > maxScore) {
        maxScore = score;
      }
    }
  }

  cout << maxScore << endl;
}
