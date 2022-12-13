#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

class BFSNode {
  public:
    pair<int, int> coords;
    bool visited;
    int distance;
    pair<int, int> prevNode;
  
  BFSNode() {
    visited = false;
    distance = -1;
  }

  BFSNode(pair<int, int> c) {
    coords = c;
    visited = false;
    distance = -1;
  }

  BFSNode(pair<int, int> c, bool v, int d, pair<int, int> p) {
    coords = c;
    visited = v;
    distance = d;
    prevNode = p;
  }

  void visit(int d, pair<int, int> prev) {
    visited = true;
    distance = d;
    prevNode = prev;
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

  int nRows = lines.size();
  int nCols = lines[0].size();
  pair<int, int> startCoords;
  pair<int, int> endCoords;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (lines[i][j] == 'S') {
        startCoords = make_pair(i, j);
      }
      if (lines[i][j] == 'E') {
        endCoords = make_pair(i, j);
      }
    }
  }
  
  list<BFSNode> queue;
  map<pair<int, int>, BFSNode> nodeMap;
  BFSNode start(endCoords, true, 0, make_pair(0, 0));
  lines[startCoords.first][startCoords.second] = 'a';
  lines[endCoords.first][endCoords.second] = 'z';
  queue.push_back(start);

  while(!queue.empty()) {
    BFSNode curNode = queue.front();
    int curX = curNode.coords.first;
    int curY = curNode.coords.second;
    queue.pop_front();
    
    pair<int, int> upCoords = make_pair(curX - 1, curY);
    if (curX > 0 && lines[curX - 1][curY] - lines[curX][curY] >= -1 && nodeMap.find(upCoords) == nodeMap.end()) {
      BFSNode up(upCoords, true, 1 + curNode.distance, curNode.coords);
      nodeMap[upCoords] = up;
      queue.push_back(up);
    }
    
    pair<int, int> rightCoords = make_pair(curX, curY + 1);
    if (curY < nCols - 1 && lines[curX][curY + 1] - lines[curX][curY] >= -1 && nodeMap.find(rightCoords) == nodeMap.end()) {
      BFSNode right(rightCoords, true, 1 + curNode.distance, curNode.coords);
      nodeMap[rightCoords] = right;
      queue.push_back(right);
    }
    
    pair<int, int> downCoords = make_pair(curX + 1, curY);
    if (curX < nRows - 1 && lines[curX + 1][curY] - lines[curX][curY] >= -1 && nodeMap.find(downCoords) == nodeMap.end()) {
      BFSNode down(downCoords, true, 1 + curNode.distance, curNode.coords);
      nodeMap[downCoords] = down;
      queue.push_back(down);
    }
    
    pair<int, int> leftCoords = make_pair(curX, curY - 1);
    if (curY > 0 && lines[curX][curY - 1] - lines[curX][curY] >= -1 && nodeMap.find(leftCoords) == nodeMap.end()) {
      BFSNode left(leftCoords, true, 1 + curNode.distance, curNode.coords);
      nodeMap[leftCoords] = left;
      queue.push_back(left);
    }
  }

  int minSteps = -1;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (lines[i][j] == 'a') {
        BFSNode node = nodeMap[make_pair(i, j)];
        int dist = node.distance;
        if ((minSteps == -1 || minSteps > dist) && node.visited) {
          minSteps = dist;
        }
      }
    } 
  }
  cout << minSteps << endl;
}
