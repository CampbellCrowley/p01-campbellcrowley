//////////////////////////////////////////
// Must be compiled with c++11 support! //
// g++ -std=c++11 guess.cpp             //
//////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Checks if inputted string is actually a number, since directly inputting an
// int from cin can crash if a character is typed instead of a number.
bool isNumber(string input) {
  if (input.length() == 0) return false;
  for (size_t i = 0; i < input.length(); i++) {
    if (!isdigit(input[i])) {
      return false;
    }
  }
  return true;
}

int convertToNum(string input) {
  if (isNumber(input)) {
    return stoi(input);
  }
  return 0;
}

void setColor(int color) { cout << "\033[1;" << color << "m"; }
void resetColor() { cout << "\033[0m"; }

bool RunGame() {
  int easyNum = 2;
  int easyTries = 1;
  int mediumNum = 10;
  int mediumTries = 2;
  int hardNum = 100;
  int hardTries = 3;

  char difficulty = '0';
  setColor(34);
  cout << "Please select difficulty:\n";
  setColor(32);
  cout << "1) Easy (1-" << easyNum << ", " << easyTries << " tr"
       << (easyTries == 1 ? "y" : "ies") << ")\n";
  setColor(33);
  cout << "2) Medium (1-" << mediumNum << ", " << mediumTries << " tr"
       << (mediumTries == 1 ? "y" : "ies") << ")\n";
  setColor(31);
  cout << "3) Hard (1-" << hardNum << ", " << hardTries << " tr"
       << (hardTries == 1 ? "y" : "ies") << ")\n";
  setColor(34);
  cout << "m====================================\n";
  cout << "High Low game /\\    \\/ Difference\n";
  cout << "====================================\n";
  setColor(32);
  cout << "A) Easy (1-" << easyNum << ", 1 try)\n";
  setColor(33);
  cout << "B) Medium (1-" << mediumNum << ", 1 try)\n";
  setColor(31);
  cout << "C) Hard (1-" << hardNum << ", 1 try)\n";
  resetColor();

  string input;
  getline(cin, input);
  difficulty = input[0];

  int currentTriesRemaining = 0;
  int maxNum = 0;
  bool isHighLowGame = true;
  switch (difficulty) {
  case '1':
    maxNum = easyNum;
    currentTriesRemaining = easyTries;
    break;
  case '2':
    maxNum = mediumNum;
    currentTriesRemaining = mediumTries;
    break;
  case '3':
    maxNum = hardNum;
    currentTriesRemaining = hardTries;
    break;
  case 'a':
  case 'A':
    maxNum = easyNum;
    currentTriesRemaining = 1;
    isHighLowGame = false;
    break;
  case 'b':
  case 'B':
    maxNum = mediumNum;
    currentTriesRemaining = 1;
    isHighLowGame = false;
    break;
  case 'c':
  case 'C':
    maxNum = hardNum;
    currentTriesRemaining = 1;
    isHighLowGame = false;
    break;
  default:
    setColor(31);
    cout << "\nInvalid difficulty.\n";
    return true;
    break;
  }
  int randomNumber = rand() % maxNum + 1;
  int guess = 0;
  while (currentTriesRemaining > 0) {
    setColor(35);
    cout << "Enter your guess between 1 and " << maxNum << " ("
         << currentTriesRemaining << " tr"
         << (currentTriesRemaining == 1 ? "y" : "ies") << " left): ";
    resetColor();
    getline(cin, input);
    if (!isNumber(input)) {
      setColor(31);
      cout << "Please enter a valid integer.\n";
      continue;
    }
    guess = convertToNum(input);
    if (guess < 1 || guess > maxNum) {
      setColor(31);
      cout << "I don't think you want to guess that number, try again.\n";
      continue;
    }

    if (guess == randomNumber) {
      setColor(32);
      cout << "Correct! The answer was " << randomNumber << "!\n";
      break;
    } else {
      setColor(31);
      cout << "Incorrect. ";
      if (isHighLowGame) {
        if (guess < randomNumber) {
          cout << "You guessed to low.\n";
        } else {
          cout << "You guessed to high.\n";
        }
      } else {
        int difference = guess - randomNumber;
        difference = difference * (difference < 0 ? -1 : 1);
        cout << "You were off by " << difference;
      }
    }
    currentTriesRemaining--;
  }
  if (isHighLowGame && currentTriesRemaining == 0) {
    cout << "The answer was " << randomNumber << ". Better luck next time!\n";
  }

  string replayChoice = "no";
  setColor(35);
  cout << "\nWould you like to play again? (y/N): ";
  resetColor();
  getline(cin, replayChoice);
  cout << endl;
  return replayChoice[0] == 'y' || replayChoice[0] == 'Y';
}

int main() {
  srand(time(NULL));
  while (RunGame()) {
    setColor(37);
    cout << "-------------------------------\n\n";
  }
}
