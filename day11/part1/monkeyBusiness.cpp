#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<u_long> splitAsInts(string s, string delimiter) {
  vector<u_long> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(stoi(token));
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(stoi(s));
  return results;
}

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

class Monke {
  public:
    vector<u_long> items;
    char operatorsymbol;
    int operand;
    int testDivisor;
    int trueMonke;
    int falseMonke;
    int nInspectedItems;

    Monke() {}

    Monke(string startingItems, string operation, string test, string ifTrue, string ifFalse) {
      items = splitAsInts(startingItems, ", ");
      string operandString = operation.substr(12);
      operatorsymbol = operandString == "old" ? '^' : operation[10];
      operand = operandString == "old" ? 2 : stoi(operandString);
      testDivisor = stoi(test.substr(13));
      trueMonke = ifTrue[16] - '0';
      falseMonke = ifFalse[16] - '0';
      nInspectedItems = 0;
    }

    void addItem(int item) {
      items.push_back(item);
    }

    void endRound() {
      nInspectedItems += items.size();
      items.clear();
    }

    void performOperation() {
      for (int i = 0; i < items.size(); i += 1) {
        u_long item = items[i];
        switch(operatorsymbol) {
          case '^': items[i] = item * item; break;
          case '*': items[i] = item * operand; break;
          case '+': items[i] = item + operand; break;
        }
      }
    }

    void lowerWorry() {
      for (int i = 0; i < items.size(); i += 1) {
        items[i] = items[i] / 3;
      }
    }

    vector<int> getNextMonkes() {
      vector<int> nextMonkes;
      for (u_long item : items) {
        nextMonkes.push_back(item % testDivisor == 0 ? trueMonke : falseMonke);
      }
      return nextMonkes;
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

  int nMonkes = lines.size() / 7 + 1;
  Monke monkes[nMonkes];
  for (int i = 0; i < nMonkes; i += 1) {
    string startingItems = lines[i * 7 + 1].substr(18);
    string operation = lines[i * 7 + 2].substr(13);
    string test = lines[i * 7 + 3].substr(8);
    string ifTrue = lines[i * 7 + 4].substr(13);
    string ifFalse = lines[i * 7 + 5].substr(14);
    Monke monke(startingItems, operation, test, ifTrue, ifFalse);
    monkes[i] = monke;
  }

  for (int n = 0; n < 20; n += 1) {
    for (int i = 0; i < nMonkes; i += 1) {
      monkes[i].performOperation();
      monkes[i].lowerWorry();
      vector<int> nextMonkes = monkes[i].getNextMonkes();
      for (int j = 0; j < nextMonkes.size(); j += 1) {
        monkes[nextMonkes[j]].addItem(monkes[i].items[j]);
      }
      monkes[i].endRound();
    }
  }

  int max1 = 0;
  int max2 = 0;
  for (int i = 0; i < nMonkes; i += 1) {
    if (monkes[i].nInspectedItems > max1) {
      max2 = max1;
      max1 = monkes[i].nInspectedItems;
    } else if (monkes[i].nInspectedItems > max2) {
      max2 = monkes[i].nInspectedItems;
    }
  }

  cout << max1 * max2 << endl;
}
