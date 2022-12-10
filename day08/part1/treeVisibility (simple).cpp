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

  int nVisibible = 2 * nCols + 2 * nRows - 4;
  for (int i = 1; i < nRows - 1; i += 1) {
    for (int j = 1; j < nCols - 1; j += 1) {
      bool visibleTop = true;
      for (int k = j - 1; k >= 0; k -= 1) {
        if (forest[i][k] >= forest[i][j]) {
          visibleTop = false;
          break;
        }
      }

      bool visibleBottom = true;
      for (int k = j + 1; k < nCols; k += 1) {
        if (forest[i][k] >= forest[i][j]) {
          visibleBottom = false;
          break;
        }
      }

      bool visibleLeft = true;
      for (int k = i - 1; k >= 0; k -= 1) {
        if (forest[k][j] >= forest[i][j]) {
          visibleLeft = false;
          break;
        }
      }

      bool visibleRight = true;
      for (int k = i + 1; k < nRows; k += 1) {
        if (forest[k][j] >= forest[i][j]) {
          visibleRight = false;
          break;
        }
      }

      if (visibleTop || visibleLeft || visibleRight || visibleBottom) {
        nVisibible += 1;
      }
    }
  }

  cout << nVisibible << endl;
}
