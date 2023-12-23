#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

int rowAndColumnToSingleIndex(int row, int column, int columnSize);
int traverse(int startRow, int startColumn, vector<bool> visitedPrior, unordered_map<int, int>& junctionCache, vector<string>& grid);

int main() {
    vector<string> grid;
    string line;

    while (getline(cin, line)) {
        grid.push_back(line);
    }
    int columnSize = grid[0].length();

    unordered_map<int, int> longestPathAtJunctions;
    vector<bool> visited(grid.size() * columnSize, false);

    cout << traverse(0, 1, visited, longestPathAtJunctions, grid) << endl;
}

int rowAndColumnToSingleIndex(int row, int column, int columnSize) {
    return (row * columnSize) + column;
}

int traverse(int startRow, int startColumn, vector<bool> visitedPrior, unordered_map<int, int>& junctionCache, vector<string>& grid) {
    int row = startRow, column = startColumn;
    int totalLength = 0;
    while (true) {
        // Did we reach the end?
        if (row == grid.size() - 1 && column == grid[0].length() - 2) {
            return totalLength;
        }

        // Visit this spot so we can't return to it
        visitedPrior[rowAndColumnToSingleIndex(row, column, grid[0].length())] = true;

        // How many paths are there?
        int pathsToTake = 0;
        bool canGoLeft = false, canGoRight = false, canGoUp = false, canGoDown = false;

        // Up
        if (grid[row][column] == '.' && row > 0 && !visitedPrior[rowAndColumnToSingleIndex(row - 1, column, grid[0].length())] && grid[row - 1][column] != '#') {
            pathsToTake++;
            canGoUp = true;
        }
        // Down
        if ((grid[row][column] == '.' || grid[row][column] == 'v') && row < grid.size() - 1 && !visitedPrior[rowAndColumnToSingleIndex(row + 1, column, grid[0].length())] && grid[row + 1][column] != '#') {
            pathsToTake++;
            canGoDown = true;
        }
        // Left
        if (grid[row][column] == '.' && column > 0 && !visitedPrior[rowAndColumnToSingleIndex(row, column - 1, grid[0].length())] && grid[row][column - 1] != '#') {
            pathsToTake++;
            canGoLeft = true;
        }
        // Right
        if ((grid[row][column] == '.' || grid[row][column] == '>') && column < grid[0].length() - 1 && !visitedPrior[rowAndColumnToSingleIndex(row, column + 1, grid[0].length())] && grid[row][column + 1] != '#') {
            pathsToTake++;
            canGoRight= true;
        }

        if (pathsToTake == 0) return 0;

        totalLength++;

        if (pathsToTake == 1) {
            // Not a junction
            if (canGoUp) {
                row--;
            }
            if (canGoDown) {
                row++;
            }
            if (canGoLeft) {
                column--;
            }
            if (canGoRight) {
                column++;
            }
            continue;
        } else {
            // We are at a junction. Have we already tried this before?
            if (junctionCache.count(rowAndColumnToSingleIndex(row, column, grid[0].length()))) {
                return totalLength + junctionCache[rowAndColumnToSingleIndex(row, column, grid[0].length())];
            } else {
                int maxValue = 0;
                if (canGoUp) {
                    maxValue = max(maxValue, traverse(row - 1, column, vector<bool>(visitedPrior.begin(), visitedPrior.end()), junctionCache, grid));
                }
                if (canGoDown) {
                    maxValue = max(maxValue, traverse(row + 1, column, vector<bool>(visitedPrior.begin(), visitedPrior.end()), junctionCache, grid));
                }
                if (canGoLeft) {
                    maxValue = max(maxValue, traverse(row, column - 1, vector<bool>(visitedPrior.begin(), visitedPrior.end()), junctionCache, grid));
                }
                if (canGoRight) {
                    maxValue = max(maxValue, traverse(row, column + 1, vector<bool>(visitedPrior.begin(), visitedPrior.end()), junctionCache, grid));
                }

                junctionCache[rowAndColumnToSingleIndex(row, column, grid[0].length())] = maxValue;
                return totalLength + maxValue;
            }
        }
    }

    return -1;
}