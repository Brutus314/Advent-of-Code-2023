#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int gearScore(vector<string>& schematic, int i, int j);
int fullNumber(vector<string>& schematic, int i, int j);

int main() {
    vector<string> schematic;
    string input;
    long long total = 0;

    while (getline(cin, input)) {
        schematic.push_back(input);
    }

    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[0].length(); j++) {
            if (schematic[i][j] == '*') {
                // This is a gear. Get its score
                total += gearScore(schematic, i, j);
            }
        }
    }

    cout << total << endl;
}

int gearScore(vector<string>& schematic, int i, int j) {
    // Must check 8 positions
    bool onFirstRow = i == 0;
    bool onFirstColumn = j == 0;
    bool onFinalRow = i == (schematic.size() - 1);
    bool onfinalColumn = j == (schematic[0].length() - 1);

    int firstNumber = 0;
    int secondNumber = 0;

    // Up
    if (!onFirstRow) {
        // Up
        if (isdigit(schematic[i - 1][j])) {
            firstNumber = fullNumber(schematic, i - 1, j);
        } else {
            // If up-middle is a number, up-left and up-right would be connected
            // Otherwise, up-left and up-right would be separate numbers

            // Up-Left
            if (!onFirstColumn) {
                if (isdigit(schematic[i - 1][j - 1])) {
                    firstNumber = fullNumber(schematic, i - 1, j - 1);
                }
            }

            // Up-Right
            if (!onfinalColumn) {
                if (isdigit(schematic[i - 1][j + 1])) {
                    if (firstNumber == 0) {
                        firstNumber = fullNumber(schematic, i - 1, j + 1);
                    } else {
                        secondNumber = fullNumber(schematic, i - 1, j + 1);
                    }
                }
            }
        }
    }

    // Same row
    if (!onFirstColumn) {
        // Left
        if (isdigit(schematic[i][j - 1])) {
            if (firstNumber == 0) {
                firstNumber = fullNumber(schematic, i, j - 1);
            } else if (secondNumber == 0) {
                secondNumber = fullNumber(schematic, i, j - 1);
            } else {
                return 0;
            };
        }
    }

    if (!onfinalColumn) {
        // Right
        if (isdigit(schematic[i][j + 1])) {
            if (firstNumber == 0) {
                firstNumber = fullNumber(schematic, i, j + 1);
            } else if (secondNumber == 0) {
                secondNumber = fullNumber(schematic, i, j + 1);
            } else {
                return 0;
            };
        }
    }

    // Down
    if (!onFinalRow) {
        // Down
        if (isdigit(schematic[i + 1][j])) {
            if (firstNumber == 0) {
                firstNumber = fullNumber(schematic, i + 1, j);
            } else if (secondNumber == 0) {
                secondNumber = fullNumber(schematic, i + 1, j);
            } else {
                return 0;
            };
        } else {
            // If down-middle is a number, down-left and down-right would be connected
            // Otherwise, down-left and down-right would be separate numbers

            // Down-Left
            if (!onFirstColumn) {
                if (isdigit(schematic[i + 1][j - 1])) {
                    if (firstNumber == 0) {
                        firstNumber = fullNumber(schematic, i + 1, j - 1);
                    } else if (secondNumber == 0) {
                        secondNumber = fullNumber(schematic, i + 1, j - 1);
                    } else {
                        return 0;
                    };
                }
            }

            // Down-Right
            if (!onfinalColumn) {
                if (isdigit(schematic[i + 1][j + 1])) {
                    if (firstNumber == 0) {
                        firstNumber = fullNumber(schematic, i + 1, j + 1);
                    } else if (secondNumber == 0) {
                        secondNumber = fullNumber(schematic, i + 1, j + 1);
                    } else {
                        return 0;
                    };
                }
            }
        }
    }

    return firstNumber * secondNumber;
}

int fullNumber(vector<string>& schematic, int i, int j) {
    int jLeft = j;
    int jRight = j;

    while (jLeft > 0 && isdigit(schematic[i][jLeft])) {
        jLeft--;
    }

    // Might be one too far. Are we on a digit? If so, must be at zero. Otherwise, push back one
    if (!isdigit(schematic[i][jLeft])) {
        jLeft++;
    }

    while (jRight < schematic[0].length() - 1 && isdigit(schematic[i][jRight])) {
        jRight++;
    }

    // Might be one too far. Are we on a digit? If so, must be at end. Otherwise, push back one
    if (!isdigit(schematic[i][jRight])) {
        jRight--;
    }

    return stoi(schematic[i].substr(jLeft, jRight - jLeft + 1));
}