#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool compareRows(vector<string>& grid, int r1, int r2, bool& smudge);
bool compareColumns(vector<string>& grid, int c1, int c2, bool& smudge);

int main() {
    string line;
    bool cinResult;
    int total = 0;
    do {
        vector<string> grid;
        while (getline(cin, line) && !line.empty()) {
            grid.push_back(line);
        }

        bool foundReflection = false;

        for (int i = 0; i < grid.size() - 1; i++) {
            bool smudge = false;
            if (compareRows(grid, i, i + 1, smudge)) {
                int up = i - 1, down = i + 2;
                bool reflection = true;
                while (up >= 0 && down < grid.size()) {
                    if (!compareRows(grid, up, down, smudge)) {
                        reflection = false;
                        break;
                    }
                    up--;
                    down++;
                }
                if (reflection && smudge) {
                    foundReflection = true;
                    total += (100 * (i + 1));
                    break;
                }
            }
        }

        if (foundReflection) {
            continue;
        }

        for (int i = 0; i < grid[0].length() - 1; i++) {
            bool smudge = false;
            if (compareColumns(grid, i, i + 1, smudge)) {
                int leftIndex = i - 1, rightIndex = i + 2;
                bool reflection = true;
                while (leftIndex >= 0 && rightIndex < grid[0].length()) {
                    if (!compareColumns(grid, leftIndex, rightIndex, smudge)) {
                        reflection = false;
                        break;
                    }
                    leftIndex--;
                    rightIndex++;
                }
                if (reflection && smudge) {
                    foundReflection = true;
                    total += (i + 1);
                    break;
                }
            }
        }

        if (!foundReflection) {
            cout << "ERROR!" << endl;
        }
    } while (!cin.eof());

    cout << total;
}

bool compareRows(vector<string>& grid, int r1, int r2, bool& smudge) {
    for (int i = 0; i < grid[r1].length(); i++) {
        if (grid[r1][i] != grid[r2][i]) {
            if (!smudge) {
                smudge = true;
            } else {
                return false;
            }
        }
    }
    return true;
}
bool compareColumns(vector<string>& grid, int c1, int c2, bool& smudge) {
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i][c1] != grid[i][c2]) {
            if (!smudge) {
                smudge = true;
            } else {
                return false;
            }
        }
    }
    return true;
}