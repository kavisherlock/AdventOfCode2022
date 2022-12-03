#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const char ROCK = 'A';
const char PAPER = 'B';
const char SCISSORS = 'C';
const char LOSE = 'X';
const char DRAW = 'Y';
const char WIN = 'Z';
const int LOSS_SCORE = 0;
const int DRAW_SCORE = 3;
const int WIN_SCORE = 6;

char getPlayerChoice(char opponent, char intendedResult) {
  if (intendedResult == DRAW) {
    return opponent;
  }
  if (intendedResult == WIN) {
    return opponent + 1 > SCISSORS ? ROCK : opponent + 1;
  }
  return opponent - 1 < ROCK ? SCISSORS : opponent - 1;
}

int getRoundScore(char opponent, char intendedResult) {
  char player = getPlayerChoice(opponent, intendedResult);
  int playerChoiceScore = (int)(player - ROCK) + 1;
  int roundScore = intendedResult == WIN ? 6 : (intendedResult == DRAW ? 3 : 0);

  return playerChoiceScore + roundScore;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  int totalScore = 0;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      char opponent = lineString[0];
      char intendedResult = lineString[2];

      totalScore += getRoundScore(opponent, intendedResult);
    }
  }
  myfile.close();

  cout << totalScore << endl;
}
