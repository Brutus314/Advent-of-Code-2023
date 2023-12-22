#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;

const int STEPS_TO_TAKE = 64;

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

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].length(), false));
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(startRow, startColumn, 0));
    int total = 0;

    while (!q.empty()) {
        int row = get<0>(q.front());
        int column = get<1>(q.front());
        int steps = get<2>(q.front());
        q.pop();

        if (row < 0 || column < 0 || row >= grid.size() || column >= grid[0].length()) {
            // Off the grid
            continue;
        }

        if (steps > STEPS_TO_TAKE) {
            // Went too far
            continue;
        }

        if (grid[row][column] == '#') {
            // It's a rock, can't be here
            continue;
        }

        if (visited[row][column]) {
            // Been here before
            continue;
        }

        visited[row][column] = true;
        if (steps % 2 == 0) {
            total++;
        }

        q.push(make_tuple(row + 1, column, steps + 1));
        q.push(make_tuple(row - 1, column, steps + 1));
        q.push(make_tuple(row, column + 1, steps + 1));
        q.push(make_tuple(row, column - 1, steps + 1));
    }

    cout << total << endl;
}