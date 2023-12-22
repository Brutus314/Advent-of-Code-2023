#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;

const long long STEPS_TO_TAKE = 26501365;

long long endableTiles(vector<string>& grid, queue<tuple<int, int, int>> q, long long stepsToTake);

int main() {
    vector<string> grid;
    string line;
    int startRow = -1, startColumn = -1;
    int index = 0;

    while (getline(cin, line)) {
        grid.push_back(line);

        if (startRow == -1) {
            int foundStart = line.find('S');
            if (foundStart > -1) {
                startRow = index;
                startColumn = foundStart;
            }
        }

        index++;
    }

    queue<tuple<int, int, int>> normalQ;
    normalQ.push(make_tuple(startRow, startColumn, 0));
    
    long long oddTiles = endableTiles(grid, normalQ, STEPS_TO_TAKE);
    long long evenTiles = endableTiles(grid, normalQ, STEPS_TO_TAKE - 1);

    queue<tuple<int, int, int>> upQ;
    upQ.push(make_tuple(grid.size() - 1, startColumn, 0));
    long long rUp = endableTiles(grid, upQ, grid.size() - 1);

    queue<tuple<int, int, int>> downQ;
    downQ.push(make_tuple(0, startColumn, 0));
    long long rDown = endableTiles(grid, downQ, grid.size() - 1);

    queue<tuple<int, int, int>> leftQ;
    leftQ.push(make_tuple(startRow, grid[0].length() - 1, 0));
    long long rLeft = endableTiles(grid, leftQ, grid[0].length() - 1);

    queue<tuple<int, int, int>> rightQ;
    rightQ.push(make_tuple(startRow, 0, 0));
    long long rRight = endableTiles(grid, rightQ, grid[0].length() - 1);

    queue<tuple<int, int, int>> upRightQ;
    upRightQ.push(make_tuple(grid.size() - 1, startColumn, 0));
    upRightQ.push(make_tuple(startRow, 0, 0));
    long long rUpRight = endableTiles(grid, upRightQ, grid.size() - 1);

    queue<tuple<int, int, int>> downRightQ;
    downRightQ.push(make_tuple(0, startColumn, 0));
    downRightQ.push(make_tuple(startRow, 0, 0));
    long long rDownRight = endableTiles(grid, downRightQ, grid.size() - 1);

    queue<tuple<int, int, int>> upLeftQ;
    upLeftQ.push(make_tuple(grid.size() - 1, startColumn, 0));
    upLeftQ.push(make_tuple(startRow, grid[0].length() - 1, 0));
    long long rUpLeft = endableTiles(grid, upLeftQ, grid[0].length() - 1);

    queue<tuple<int, int, int>> downLeftQ;
    downLeftQ.push(make_tuple(0, startColumn, 0));
    downLeftQ.push(make_tuple(startRow, grid[0].length() - 1, 0));
    long long rDownLeft = endableTiles(grid, downLeftQ, grid[0].length() - 1);

    queue<tuple<int, int, int>> upRightCornerQ;
    upRightCornerQ.push(make_tuple(0, grid[0].length() - 1, 0));
    long long rUpRightCorner = endableTiles(grid, upRightCornerQ, ((grid.size() - 1) / 2) - 1);

    queue<tuple<int, int, int>> downRightCornerQ;
    downRightCornerQ.push(make_tuple(grid.size() - 1, grid[0].length() - 1, 0));
    long long rDownRightCorner = endableTiles(grid, downRightCornerQ, ((grid.size() - 1) / 2) - 1);

    queue<tuple<int, int, int>> upLeftCornerQ;
    upLeftCornerQ.push(make_tuple(0, 0, 0));
    long long rUpLeftCorner = endableTiles(grid, upLeftCornerQ, ((grid.size() - 1) / 2) - 1);

    queue<tuple<int, int, int>> downLeftCornerQ;
    downLeftCornerQ.push(make_tuple(grid.size() - 1, 0, 0));
    long long rDownLeftCorner = endableTiles(grid, downLeftCornerQ, ((grid.size() - 1) / 2) - 1);

    long long total = 0;
    long long startStraightPaths = STEPS_TO_TAKE / grid.size();
    
    total += (startStraightPaths * startStraightPaths) * ((startStraightPaths % 2 == 1) ? oddTiles : evenTiles);
    total += ((startStraightPaths - 1) * (startStraightPaths - 1)) * ((startStraightPaths % 2 == 0) ? oddTiles : evenTiles);

    total += rUp;
    total += rLeft;
    total += rDown;
    total += rRight;

    cout << (startStraightPaths - 1) * rUpRight << endl;

    total += (startStraightPaths - 1) * rUpRight;
    total += (startStraightPaths - 1) * rUpLeft;
    total += (startStraightPaths - 1) * rDownLeft;
    total += (startStraightPaths - 1) * rDownRight;

    total += startStraightPaths * rUpRightCorner;
    total += startStraightPaths * rUpLeftCorner;
    total += startStraightPaths * rDownRightCorner;
    total += startStraightPaths * rDownLeftCorner;

    cout << total << endl;
}

long long endableTiles(vector<string>& grid, queue<tuple<int, int, int>> q, long long stepsToTake) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].length(), false));
    long long total = 0;

    while (!q.empty()) {
        int row = get<0>(q.front());
        int column = get<1>(q.front());
        int steps = get<2>(q.front());
        q.pop();

        if (row < 0 || column < 0 || row >= grid.size() || column >= grid[0].length()) {
            // Off the grid
            continue;
        }

        if (grid[row][column] == '#') {
            // It's a rock, can't be here
            continue;
        }

        if (steps > stepsToTake) {
            continue;
        }

        if (visited[row][column]) {
            // Been here before
            continue;
        }

        visited[row][column] = true;
        if ((steps % 2) == (stepsToTake % 2)) {
            total++;
        }

        q.push(make_tuple(row + 1, column, steps + 1));
        q.push(make_tuple(row - 1, column, steps + 1));
        q.push(make_tuple(row, column + 1, steps + 1));
        q.push(make_tuple(row, column - 1, steps + 1));
    }

    return total;
}