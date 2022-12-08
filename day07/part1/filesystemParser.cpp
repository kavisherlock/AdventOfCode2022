#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

class Item {
  public:
    string type;
    string name;
    int size;
    vector<Item*> children;
    Item *parent;

    Item() {}

    Item(string t, string n, int s, Item* p) {
      type = t;
      name = n;
      size = s;
      parent = p;
    }
};

int calculateItemSizes(Item *item) {
  if (item->size > 0) {
    return item->size;
  }

  int size = 0;

  for (Item* child : item->children) {
    if (item->type == "FILE") {
      size += item->size;
    } else {
      size += calculateItemSizes(child);
    }
  }

  item->size = size;
  return size;
}

int getSmallDirSizes(Item *item) {
  int size = 0;
  if (item->size < 100000 && item->type == "DIR") {
    size += item->size;
  }

  for (Item* child : item->children) {
    if (item->type == "DIR") {
      size += getSmallDirSizes(child);
    }
  }

  return size;
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

  Item *root;
  Item *curDir;
  string nextDir;
  for (string command : lines) {
    if (command[0] == '$') {
      if (command[2] == 'c') {
        nextDir = command.substr(5);
        if (nextDir == "..") {
          curDir = curDir->parent;
        } else if (nextDir == "/") {
          Item* item = new Item("DIR", "root", 0, nullptr);
          root = item;
          curDir = item;
        } else {
          for (Item* child : curDir->children) {
            if (child->name == nextDir) {
              curDir = child;
              break;
            }
          }
        }
      }
    } else {
      vector<string> lsItem = split(command, " ");
      string itemName = lsItem[1];
      if (lsItem[0] == "dir") {
        Item* item = new Item("DIR", itemName, 0, curDir);
        curDir->children.push_back(item);
      } else {
        Item* item = new Item("FILE", itemName, stoi(lsItem[0]), curDir);
        curDir->children.push_back(item);
      }
    }
  }

  cout << calculateItemSizes(root) << endl;
  cout << getSmallDirSizes(root) << endl;
}
