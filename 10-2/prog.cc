#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

bool pipeIsLeftFacing(char p);
bool pipeIsUpFacing(char p);
bool pipeIsRightFacing(char p);
bool pipeIsDownFacing(char p);
vector<pair<int, int>> getLoop(vector<string>& grid, int startRow, int startColumn);
bool traverse(vector<string>& grid, int& row, int& column, int& fromRow, int& fromColumn);

const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

int main() {
    int rowIndex = 0;
    int startRow = -1, startColumn = -1;
    string line;
    vector<string> grid;

    while (getline(cin, line)) {
        grid.push_back(line);
        if (startRow == -1) {
            int columnIndex = line.find('S');
            if (columnIndex != -1) {
                startRow = rowIndex;
                startColumn = columnIndex;
            }
        }
        rowIndex++;
    }

    // Find the correct pipe for S and replace it
    int length;
    grid[startRow][startColumn] = '|';
    vector<pair<int, int>> loop = getLoop(grid, startRow, startColumn);

    if (loop.size() == 0) {
        grid[startRow][startColumn] = '7';
        loop = getLoop(grid, startRow, startColumn);
    }

    if (loop.size() == 0) {
        grid[startRow][startColumn] = 'J';
        loop = getLoop(grid, startRow, startColumn);
    }

    if (loop.size() == 0) {
        grid[startRow][startColumn] = 'F';
        loop = getLoop(grid, startRow, startColumn);
    }

    if (loop.size() == 0) {
        grid[startRow][startColumn] = '-';
        loop = getLoop(grid, startRow, startColumn);
    }

    if (loop.size() == 0) {
        grid[startRow][startColumn] = 'L';
        loop = getLoop(grid, startRow, startColumn);
    }

    int total = 0;
    vector<vector<bool>> isLoop(grid.size(), vector<bool>(grid[0].size(), false));
    for (int i = 0; i < loop.size(); i++) {
        isLoop[loop[i].first][loop[i].second] = true;
    }

    // Check everything to see if we can reach the outside
    for (int i = 0; i < grid.size(); i++) {
        bool isInside = false;
        for (int j = 0; j < grid[i].size(); j++) {
            if (isLoop[i][j] && (grid[i][j] == '|' || grid[i][j] == 'L' || grid[i][j] == 'J')) {
                isInside = !isInside;
            } else if (!isLoop[i][j]) {
                if (isInside) total++;
            }
        }
    }

    cout << total << endl;
}

bool pipeIsLeftFacing(char p) {
    return (p == '-') || (p == '7') || (p == 'J');
}

bool pipeIsUpFacing(char p) {
    return (p == '|') || (p == 'L') || (p == 'J');
}

bool pipeIsRightFacing(char p) {
    return (p == '-') || (p == 'L') || (p == 'F');
}

bool pipeIsDownFacing(char p) {
    return (p == '|') || (p == '7') || (p == 'F');
}

vector<pair<int, int>> getLoop(vector<string>& grid, int startRow, int startColumn) {
    int length = 0;
    int curRow = startRow, curColumn = startColumn;
    int prevRow = -1, prevColumn = -1;
    vector<pair<int, int>> loop;
    // Take the first step, then loop until back to start
    if (traverse(grid, curRow, curColumn, prevRow, prevColumn)) {
        length++;
        loop.push_back(make_pair(prevRow, prevColumn));
        while ((curRow != startRow || curColumn != startColumn) && traverse(grid, curRow, curColumn, prevRow, prevColumn)) {
            length++;
            loop.push_back(make_pair(prevRow, prevColumn));
        }
        if (curRow == startRow && curColumn == startColumn) {
            return loop;
        } else {
            return vector<pair<int, int>>(0);
        }
    } else {
        return vector<pair<int, int>>(0);
    }
}

// Tries to traverse through the current pipe, ignoring the pipe that this one was traversed from
bool traverse(vector<string>& grid, int& row, int& column, int& fromRow, int& fromColumn) {
    switch(grid[row][column]) {
        case '-':
            if (column + 1 == fromColumn) {
                // Move left
                if (column > 0 && pipeIsRightFacing(grid[row][column - 1])) {
                    fromColumn = column;
                    fromRow = row;
                    column--;
                    return true;
                } else {
                    // Cannot move left
                    return false;
                }
            } else {
                // Move right
                if (column < grid[0].size() - 1 && pipeIsLeftFacing(grid[row][column + 1])) {
                    fromColumn = column;
                    fromRow = row;
                    column++;
                    return true;
                } else {
                    // Cannot move right
                    return false;
                }
            }
            break;
        case '|':
            if (row + 1 == fromRow) {
                // Move up
                if (row > 0 && pipeIsDownFacing(grid[row - 1][column])) {
                    fromColumn = column;
                    fromRow = row;
                    row--;
                    return true;
                } else {
                    // Cannot move up
                    return false;
                }
            } else {
                // Move down
                if (row < grid.size() - 1 && pipeIsUpFacing(grid[row + 1][column])) {
                    fromColumn = column;
                    fromRow = row;
                    row++;
                    return true;
                } else {
                    // Cannot move down
                    return false;
                }
            }
            break;
        case 'F':
            if (row + 1 == fromRow) {
                // Move right
                if (column < grid[0].size() - 1 && pipeIsLeftFacing(grid[row][column + 1])) {
                    fromColumn = column;
                    fromRow = row;
                    column++;
                    return true;
                } else {
                    // Cannot move right
                    return false;
                }
            } else {
                // Move down
                if (row < grid.size() - 1 && pipeIsUpFacing(grid[row + 1][column])) {
                    fromColumn = column;
                    fromRow = row;
                    row++;
                    return true;
                } else {
                    // Cannot move down
                    return false;
                }
            }
            break;
        case '7':
            if (row + 1 == fromRow) {
                // Move left
                if (column > 0 && pipeIsRightFacing(grid[row][column - 1])) {
                    fromColumn = column;
                    fromRow = row;
                    column--;
                    return true;
                } else {
                    // Cannot move left
                    return false;
                }
            } else {
                // Move down
                if (row < grid.size() - 1 && pipeIsUpFacing(grid[row + 1][column])) {
                    fromColumn = column;
                    fromRow = row;
                    row++;
                    return true;
                } else {
                    // Cannot move down
                    return false;
                }
            }
            break;
        case 'J':
            if (row - 1 == fromRow) {
                // Move left
                if (column > 0 && pipeIsRightFacing(grid[row][column - 1])) {
                    fromColumn = column;
                    fromRow = row;
                    column--;
                    return true;
                } else {
                    // Cannot move left
                    return false;
                }
            } else {
                // Move up
                if (row > 0 && pipeIsDownFacing(grid[row - 1][column])) {
                    fromColumn = column;
                    fromRow = row;
                    row--;
                    return true;
                } else {
                    // Cannot move up
                    return false;
                }
            }
            break;
        case 'L':
            if (row - 1 == fromRow) {
                // Move right
                if (column < grid[0].size() - 1 && pipeIsLeftFacing(grid[row][column + 1])) {
                    fromColumn = column;
                    fromRow = row;
                    column++;
                    return true;
                } else {
                    // Cannot move right
                    return false;
                }
            } else {
                // Move up
                if (row > 0 && pipeIsDownFacing(grid[row - 1][column])) {
                    fromColumn = column;
                    fromRow = row;
                    row--;
                    return true;
                } else {
                    // Cannot move up
                    return false;
                }
            }
            break;
        default:
            return false;
    }
}