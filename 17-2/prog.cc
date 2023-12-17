#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

int main() {
    string line;
    vector<vector<int>> grid;

    while (getline(cin, line)) {
        grid.push_back(vector<int>());
        for (int i = 0; i < line.length(); i++) {
            grid.back().push_back(line[i] - '0');
        }
    }

    vector<vector<vector<vector<int>>>> heats(4, vector<vector<vector<int>>>(10, vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), INT32_MAX))));

    heats[LEFT][0][0][0] = 0;
    heats[RIGHT][0][0][0] = 0;
    heats[UP][0][0][0] = 0;
    heats[DOWN][0][0][0] = 0;

    queue<tuple<int, int, int, int>> check;
    check.push(make_tuple(0, 0, DOWN, 0));
    check.push(make_tuple(0, 0, RIGHT, 0));

    while (!check.empty()) {
        int row = get<0>(check.front());
        int column = get<1>(check.front());
        int direction = get<2>(check.front());
        int straightSpaces = get<3>(check.front());
        check.pop();
        if (row == grid.size() - 1 && column == grid[0].size() - 1) {
            continue;
        }
        int currentHeat;
        bool horizontal = (direction == LEFT || direction == RIGHT);
        if (row == 0 && column == 0) {
            currentHeat = 0;
        } else {
            currentHeat = heats[direction][straightSpaces - 1][row][column];
        }
        int nextStraightSpaces;

        // Move up
        if (row > 0 && direction != DOWN && ((direction == UP && straightSpaces < 10) || (direction != UP && straightSpaces >= 4))) {
            nextStraightSpaces = (direction == UP ? straightSpaces + 1 : 1);
            if (currentHeat + grid[row - 1][column] < heats[UP][nextStraightSpaces - 1][row - 1][column]) {
                check.push(make_tuple(row - 1, column, UP, nextStraightSpaces));
                heats[UP][nextStraightSpaces - 1][row - 1][column] = currentHeat + grid[row - 1][column];
            }
        }

        // Move down
        if (row < grid.size() - 1 && direction != UP && ((direction == DOWN && straightSpaces < 10) || (direction != DOWN && straightSpaces >= 4))) {
            nextStraightSpaces = (direction == DOWN ? straightSpaces + 1 : 1);
            if (currentHeat + grid[row + 1][column] < heats[DOWN][nextStraightSpaces - 1][row + 1][column]) {
                check.push(make_tuple(row + 1, column, DOWN, nextStraightSpaces));
                heats[DOWN][nextStraightSpaces - 1][row + 1][column] = currentHeat + grid[row + 1][column];
            }
        }

        // Move left
        if (column > 0 && direction != RIGHT && ((direction == LEFT && straightSpaces < 10) || (direction != LEFT && straightSpaces >= 4))) {
            nextStraightSpaces = (direction == LEFT ? straightSpaces + 1 : 1);
            if (currentHeat + grid[row][column - 1] < heats[LEFT][nextStraightSpaces - 1][row][column - 1]) {
                check.push(make_tuple(row, column - 1, LEFT, nextStraightSpaces));
                heats[LEFT][nextStraightSpaces - 1][row][column - 1] = currentHeat + grid[row][column - 1];
            }
        }

        // Move right
        if (column < grid[0].size() - 1 && direction != LEFT && ((direction == RIGHT && straightSpaces < 10) || (direction != RIGHT && straightSpaces >= 4))) {
            nextStraightSpaces = (direction == RIGHT ? straightSpaces + 1 : 1);
            if (currentHeat + grid[row][column + 1] < heats[RIGHT][nextStraightSpaces - 1][row][column + 1]) {
                check.push(make_tuple(row, column + 1, RIGHT, nextStraightSpaces));
                heats[RIGHT][nextStraightSpaces - 1][row][column + 1] = currentHeat + grid[row][column + 1];
            }
        }
    }

    int minimum = INT32_MAX;

    for (int i = 0; i < 4; i++) {
        for (int j = 3; j < 10; j++) {
            if (heats[i][j].back().back() < minimum) {
                minimum = heats[i][j].back().back();
            }
        }
    }

    cout << minimum << endl;
}