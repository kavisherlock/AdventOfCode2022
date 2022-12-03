#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const char OPPONENT_ROCK = 'A';
const char OPPONENT_PAPER = 'B';
const char OPPONENT_SCISSORS = 'C';
const char PLAYER_ROCK = 'X';
const char PLAYER_PAPER = 'Y';
const char PLAYER_SCISSORS = 'Z';
const int LOSS_SCORE = 0;
const int DRAW_SCORE = 3;
const int WIN_SCORE = 6;

int getRoundScore(char player, char opponent) {
  int playerChoiceScore = (int)(player - PLAYER_ROCK) + 1;
  int roundScore = 0;

  if (player - PLAYER_ROCK == opponent - OPPONENT_ROCK) {
    roundScore = DRAW_SCORE;
  } else {
    if (player == PLAYER_ROCK) {
      roundScore = opponent == OPPONENT_PAPER ? LOSS_SCORE : WIN_SCORE;
    }
    if (player == PLAYER_PAPER) {
      roundScore = opponent == OPPONENT_SCISSORS ? LOSS_SCORE : WIN_SCORE;
    }
    if (player == PLAYER_SCISSORS) {
      roundScore = opponent == OPPONENT_ROCK ? LOSS_SCORE : WIN_SCORE;
    }
  }

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
      char player = lineString[2];

      totalScore += getRoundScore(player, opponent);
    }
  }
  myfile.close();

  cout << totalScore << endl;
}
