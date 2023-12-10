#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool pipeIsLeftFacing(char p);
bool pipeIsUpFacing(char p);
bool pipeIsRightFacing(char p);
bool pipeIsDownFacing(char p);
int loopLength(vector<string>& grid, int startRow, int startColumn);
bool traverse(vector<string>& grid, int& row, int& column, int& fromRow, int& fromColumn);

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

    int length;

    grid[startRow][startColumn] = '|';
    length = loopLength(grid, startRow, startColumn);
    if (length != -1) {
        cout << length / 2 << endl;
        exit(EXIT_SUCCESS);
    }

    grid[startRow][startColumn] = '7';
    length = loopLength(grid, startRow, startColumn);
    if (length != -1) {
        cout << length / 2 << endl;
        exit(EXIT_SUCCESS);
    }

    grid[startRow][startColumn] = 'J';
    length = loopLength(grid, startRow, startColumn);
    if (length != -1) {
        cout << length / 2 << endl;
        exit(EXIT_SUCCESS);
    }

    grid[startRow][startColumn] = 'F';
    length = loopLength(grid, startRow, startColumn);
    if (length != -1) {
        cout << length / 2 << endl;
        exit(EXIT_SUCCESS);
    }

    grid[startRow][startColumn] = '-';
    length = loopLength(grid, startRow, startColumn);
    if (length != -1) {
        cout << length / 2 << endl;
        exit(EXIT_SUCCESS);
    }

    grid[startRow][startColumn] = 'L';
    length = loopLength(grid, startRow, startColumn);
    if (length != -1) {
        cout << length / 2 << endl;
        exit(EXIT_SUCCESS);
    }

    cout << "PROBLEM: NO LOOP FOUND" << endl;
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

int loopLength(vector<string>& grid, int startRow, int startColumn) {
    int length = 0;
    int curRow = startRow, curColumn = startColumn;
    int prevRow = -1, prevColumn = -1;
    // Take the first step, then loop until back to start
    if (traverse(grid, curRow, curColumn, prevRow, prevColumn)) {
        length++;
        while ((curRow != startRow || curColumn != startColumn) && traverse(grid, curRow, curColumn, prevRow, prevColumn)) {
            length++;
        }
        if (curRow == startRow && curColumn == startColumn) {
            return length;
        } else {
            return -1;
        }
    } else {
        return -1;
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