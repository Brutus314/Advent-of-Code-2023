#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool numberAdjacentToSymbol(vector<string>& schematic, int i, int j);
int fullNumber(vector<string>& schematic, int i, int& j);

int main() {
    vector<string> schematic;
    string input;
    int total = 0;

    while (getline(cin, input)) {
        schematic.push_back(input);
    }

    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[0].length(); j++) {
            if (isdigit(schematic[i][j])) {
                // This is a number. Is it adjacent to a symbol?
                if (numberAdjacentToSymbol(schematic, i, j)) {
                    // Need to get the full number (and then modify j so we don't double-count)
                    total += fullNumber(schematic, i, j);
                }
            }
        }
    }

    cout << total << endl;
}

bool numberAdjacentToSymbol(vector<string>& schematic, int i, int j) {
    // Must check 8 positions
    bool onFirstRow = i == 0;
    bool onFirstColumn = j == 0;
    bool onFinalRow = i == (schematic.size() - 1);
    bool onfinalColumn = j == (schematic[0].length() - 1);

    // Up
    if (!onFirstRow) {
        // Up-Left
        if (!onFirstColumn) {
            if (!isdigit(schematic[i - 1][j - 1]) && schematic[i - 1][j - 1] != '.') {
                return true;
            }
        }

        // Up
        if (!isdigit(schematic[i - 1][j]) && schematic[i - 1][j] != '.') {
            return true;
        }

        // Up-Right
        if (!onfinalColumn) {
            if (!isdigit(schematic[i - 1][j + 1]) && schematic[i - 1][j + 1] != '.') {
                return true;
            }
        }
    }

    // Same row
    if (!onFirstColumn) {
        // Left
        if (!isdigit(schematic[i][j - 1]) && schematic[i][j - 1] != '.') {
            return true;
        }
    }

    if (!onfinalColumn) {
        // Right
        if (!isdigit(schematic[i][j + 1]) && schematic[i][j + 1] != '.') {
            return true;
        }
    }

    // Down
    if (!onFinalRow) {
        // Down-Left
        if (!onFirstColumn) {
            if (!isdigit(schematic[i + 1][j - 1]) && schematic[i + 1][j - 1] != '.') {
                return true;
            }
        }

        // Down
        if (!isdigit(schematic[i + 1][j]) && schematic[i + 1][j] != '.') {
            return true;
        }

        // Down-Right
        if (!onfinalColumn) {
            if (!isdigit(schematic[i + 1][j + 1]) && schematic[i + 1][j + 1] != '.') {
                return true;
            }
        }
    }

    return false;
}

int fullNumber(vector<string>& schematic, int i, int& j) {
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

    j = jRight;
    return stoi(schematic[i].substr(jLeft, jRight - jLeft + 1));
}