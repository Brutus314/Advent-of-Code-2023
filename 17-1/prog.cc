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

    vector<vector<vector<int>>> verticalHeat(3, vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), INT32_MAX)));
    vector<vector<vector<int>>> horizontalHeat(3, vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), INT32_MAX)));

    verticalHeat[0][0][0] = 0;
    horizontalHeat[0][0][0] = 0;

    queue<tuple<int, int, int, int>> check;
    check.push(make_tuple(0, 0, -1, 0));

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
            currentHeat = (horizontal ? horizontalHeat[straightSpaces - 1][row][column] : verticalHeat[straightSpaces - 1][row][column]);
        }
        int nextStraightSpaces;

        // Move up
        if (row > 0 && direction != DOWN && (horizontal || straightSpaces < 3)) {
            nextStraightSpaces = (horizontal ? 1 : straightSpaces + 1);
            if (currentHeat + grid[row - 1][column] < verticalHeat[nextStraightSpaces - 1][row - 1][column]) {
                check.push(make_tuple(row - 1, column, UP, nextStraightSpaces));
                verticalHeat[nextStraightSpaces - 1][row - 1][column] = currentHeat + grid[row - 1][column];
            }
        }

        // Move down
        if (row < grid.size() - 1 && direction != UP && (horizontal || straightSpaces < 3)) {
            nextStraightSpaces = (horizontal ? 1 : straightSpaces + 1);
            if (currentHeat + grid[row + 1][column] < verticalHeat[nextStraightSpaces - 1][row + 1][column]) {
                check.push(make_tuple(row + 1, column, DOWN, nextStraightSpaces));
                verticalHeat[nextStraightSpaces - 1][row + 1][column] = currentHeat + grid[row + 1][column];
            }
        }

        // Move left
        if (column > 0 && direction != RIGHT && (!horizontal || straightSpaces < 3)) {
            nextStraightSpaces = (horizontal ? straightSpaces + 1 : 1);
            if (currentHeat + grid[row][column - 1] < horizontalHeat[nextStraightSpaces - 1][row][column - 1]) {
                check.push(make_tuple(row, column - 1, LEFT, nextStraightSpaces));
                horizontalHeat[nextStraightSpaces - 1][row][column - 1] = currentHeat + grid[row][column - 1];
            }
        }

        // Move right
        if (column < grid[0].size() - 1 && direction != LEFT && (!horizontal || straightSpaces < 3)) {
            nextStraightSpaces = (horizontal ? straightSpaces + 1 : 1);
            if (currentHeat + grid[row][column + 1] < horizontalHeat[nextStraightSpaces - 1][row][column + 1]) {
                check.push(make_tuple(row, column + 1, RIGHT, nextStraightSpaces));
                horizontalHeat[nextStraightSpaces - 1][row][column + 1] = currentHeat + grid[row][column + 1];
            }
        }
    }

    int minimum = INT32_MAX;

    for (int i = 0; i < 3; i++) {
        int x = min(horizontalHeat[i].back().back(), verticalHeat[i].back().back());
        if (x < minimum) {
            minimum = x;
        }
    }

    cout << minimum << endl;
}