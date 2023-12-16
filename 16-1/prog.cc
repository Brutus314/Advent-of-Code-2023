#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "tile.hpp"

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

using namespace std;

bool nextTileExists(int curRow, int curColumn, vector<string>& grid, int direction, int& nextRow, int& nextColumn);
int forwardSlashReflection(int direction);
int backSlashReflection(int direction);

int main() {
    string line;
    vector<string> grid;
    vector<vector<tile>> energizedGrid;

    while (getline(cin, line)) {
        grid.push_back(line);
        energizedGrid.push_back(vector<tile>(line.length(), tile()));
    }

    vector<tuple<int, int, int>> queue;
    queue.push_back(make_tuple(0, 0, RIGHT));
    energizedGrid[0][0].setRight();

    while (!queue.empty()) {
        tuple<int, int, int> indexes = queue.back();
        queue.pop_back();

        int row = get<0>(indexes);
        int column = get<1>(indexes);
        int direction = get<2>(indexes);

        int nextRow, nextColumn, nextDirection;

        switch (grid[row][column]) {
            case '.':
                if (nextTileExists(row, column, grid, direction, nextRow, nextColumn)) {
                    if (!energizedGrid[nextRow][nextColumn].energized(direction)) {
                        energizedGrid[nextRow][nextColumn].setEnergized(direction);
                        queue.push_back(make_tuple(nextRow, nextColumn, direction));
                    }
                }
                break;
            case '-':
                if (direction == LEFT || direction == RIGHT) {
                    if (nextTileExists(row, column, grid, direction, nextRow, nextColumn)) {
                        if (!energizedGrid[nextRow][nextColumn].energized(direction)) {
                            energizedGrid[nextRow][nextColumn].setEnergized(direction);
                            queue.push_back(make_tuple(nextRow, nextColumn, direction));
                        }
                    }
                } else {
                    if (nextTileExists(row, column, grid, LEFT, nextRow, nextColumn)) {
                        if (!energizedGrid[nextRow][nextColumn].leftEnergized()) {
                            energizedGrid[nextRow][nextColumn].setLeft();
                            queue.push_back(make_tuple(nextRow, nextColumn, LEFT));
                        }
                    }
                    if (nextTileExists(row, column, grid, RIGHT, nextRow, nextColumn)) {
                        if (!energizedGrid[nextRow][nextColumn].rightEnergized()) {
                            energizedGrid[nextRow][nextColumn].setRight();
                            queue.push_back(make_tuple(nextRow, nextColumn, RIGHT));
                        }
                    }
                }
                break;
            case '|':
                if (direction == UP || direction == DOWN) {
                    if (nextTileExists(row, column, grid, direction, nextRow, nextColumn)) {
                        if (!energizedGrid[nextRow][nextColumn].energized(direction)) {
                            energizedGrid[nextRow][nextColumn].setEnergized(direction);
                            queue.push_back(make_tuple(nextRow, nextColumn, direction));
                        }
                    }
                } else {
                    if (nextTileExists(row, column, grid, UP, nextRow, nextColumn)) {
                        if (!energizedGrid[nextRow][nextColumn].upEnergized()) {
                            energizedGrid[nextRow][nextColumn].setUp();
                            queue.push_back(make_tuple(nextRow, nextColumn, UP));
                        }
                    }
                    if (nextTileExists(row, column, grid, DOWN, nextRow, nextColumn)) {
                        if (!energizedGrid[nextRow][nextColumn].downEnergized()) {
                            energizedGrid[nextRow][nextColumn].setDown();
                            queue.push_back(make_tuple(nextRow, nextColumn, DOWN));
                        }
                    }
                }
                break;
            case '/':
                nextDirection = forwardSlashReflection(direction);
                if (nextTileExists(row, column, grid, nextDirection, nextRow, nextColumn)) {
                    if (!energizedGrid[nextRow][nextColumn].energized(nextDirection)) {
                        energizedGrid[nextRow][nextColumn].setEnergized(nextDirection);
                        queue.push_back(make_tuple(nextRow, nextColumn, nextDirection));
                    }
                }
                break;
            case '\\':
                nextDirection = backSlashReflection(direction);
                if (nextTileExists(row, column, grid, nextDirection, nextRow, nextColumn)) {
                    if (!energizedGrid[nextRow][nextColumn].energized(nextDirection)) {
                        energizedGrid[nextRow][nextColumn].setEnergized(nextDirection);
                        queue.push_back(make_tuple(nextRow, nextColumn, nextDirection));
                    }
                }
                break;
        }
    }

    int total = 0;
    for (int i = 0; i < energizedGrid.size(); i++) {
        for (int j = 0; j < energizedGrid[i].size(); j++) {
            if (energizedGrid[i][j].anyEnergized()) {
                total++;
            }
        }
    }

    cout << total << endl;
}

bool nextTileExists(int curRow, int curColumn, vector<string>& grid, int direction, int& nextRow, int& nextColumn) {
    bool hasNextTile;
    switch (direction) {
        case LEFT:
            hasNextTile = (curColumn > 0);
            nextRow = curRow;
            nextColumn = curColumn - 1;
            break;
        case RIGHT:
            hasNextTile = (curColumn < grid[curRow].length() - 1);
            nextRow = curRow;
            nextColumn = curColumn + 1;
            break;
        case UP:
            hasNextTile = (curRow > 0);
            nextColumn = curColumn;
            nextRow = curRow - 1;
            break;
        case DOWN:
            hasNextTile = (curRow < grid.size() - 1);
            nextColumn = curColumn;
            nextRow = curRow + 1;
            break;
    }
    return hasNextTile;
}

int forwardSlashReflection(int direction) {
    if (direction == LEFT) {
        return DOWN;
    }
    if (direction == RIGHT) {
        return UP;
    }
    if (direction == UP) {
        return RIGHT;
    }
    return LEFT;
}

int backSlashReflection(int direction) {
    if (direction == LEFT) {
        return UP;
    }
    if (direction == RIGHT) {
        return DOWN;
    }
    if (direction == UP) {
        return LEFT;
    }
    return RIGHT;
}