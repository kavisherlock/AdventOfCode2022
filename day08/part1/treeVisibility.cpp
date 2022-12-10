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

  bool leftRightVisibility[nRows][nCols];
  for (int i = 0; i < nRows; i += 1) {
    int tallestTreeHeight = -1;
    for (int j = 1; j < nCols - 1; j += 1) {
      if (forest[i][j] >= tallestTreeHeight) {
        tallestTreeHeight = forest[i][j];
      }
    }
    int leftMostTallestTree = -1;
    for (int j = 1; j < nCols - 1; j += 1) {
      if (forest[i][j] == tallestTreeHeight) {
        leftMostTallestTree = j;
        break;
      }
    }
    int rightMostTallestTree = -1;
    for (int j = nCols - 2; j >= 1; j -= 1) {
      if (forest[i][j] == tallestTreeHeight) {
        rightMostTallestTree = j;
        break;
      }
    }

    leftRightVisibility[i][0] = true;
    for (int j = 1; j <= leftMostTallestTree; j += 1) {
      bool isTreeVisible = true;
      for (int k = j - 1; k >= 0; k -= 1) {
        if (forest[i][j] <= forest[i][k]) {
          isTreeVisible = false;
          break;
        }
      }
      leftRightVisibility[i][j] = isTreeVisible;
    }
    for (int j = leftMostTallestTree + 1; j < rightMostTallestTree; j += 1) {
      leftRightVisibility[i][j] = false;
    }
    for (int j = rightMostTallestTree; j < nCols - 1; j += 1) {
      bool isTreeVisible = true;
      for (int k = j + 1; k < nCols; k += 1) {
        if (forest[i][j] <= forest[i][k]) {
          isTreeVisible = false;
          break;
        }
      }
      leftRightVisibility[i][j] = isTreeVisible;
    }
    if (leftMostTallestTree == rightMostTallestTree) {
      leftRightVisibility[i][leftMostTallestTree] = forest[i][nCols - 1] < forest[i][leftMostTallestTree] || forest[i][0] < forest[i][leftMostTallestTree];
    }
    leftRightVisibility[i][nCols - 1] = true;
  }

  bool topBottomVisibility[nRows][nCols];
  for (int j = 0; j < nCols; j += 1) {
    int tallestTreeHeight = -1;
    for (int i = 1; i < nRows - 1; i += 1) {
      if (forest[i][j] >= tallestTreeHeight) {
        tallestTreeHeight = forest[i][j];
      }
    }
    int topMostTallestTree = -1;
    for (int i = 1; i < nRows - 1; i += 1) {
      if (forest[i][j] == tallestTreeHeight) {
        topMostTallestTree = i;
        break;
      }
    }
    int bottomMostTallestTree = -1;
    for (int i = nRows - 2; i >= 1; i -= 1) {
      if (forest[i][j] == tallestTreeHeight) {
        bottomMostTallestTree = i;
        break;
      }
    }

    topBottomVisibility[0][j] = true;
    for (int i = 1; i <= topMostTallestTree; i += 1) {
      bool isTreeVisible = true;
      for (int k = i - 1; k >= 0; k -= 1) {
        if (forest[i][j] <= forest[k][j]) {
          isTreeVisible = false;
          break;
        }
      }
      topBottomVisibility[i][j] = isTreeVisible;
    }
    for (int i = topMostTallestTree + 1; i < bottomMostTallestTree; i += 1) {
      topBottomVisibility[i][j] = false;
    }
    for (int i = bottomMostTallestTree; i < nRows - 1; i += 1) {
      bool isTreeVisible = true;
      for (int k = i + 1; k < nRows; k += 1) {
        if (forest[i][j] <= forest[k][j]) {
          isTreeVisible = false;
          break;
        }
      }
      topBottomVisibility[i][j] = isTreeVisible;
    }
    if (topMostTallestTree == bottomMostTallestTree) {
      topBottomVisibility[topMostTallestTree][j] = forest[nRows - 1][j] < forest[topMostTallestTree][j] || forest[0][j] < forest[topMostTallestTree][j];
    }
    topBottomVisibility[nRows - 1][j] = true;
  }

  int visibleTreesCount = 0;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (leftRightVisibility[i][j] || topBottomVisibility[i][j]) {
        visibleTreesCount += 1;
      }
    }
  }
  cout << visibleTreesCount << endl;
}
