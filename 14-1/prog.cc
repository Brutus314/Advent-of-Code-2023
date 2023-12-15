#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> grid;
    int total = 0;
    string line;

    while (getline(cin, line)) {
        grid.push_back(line);
    }

    vector<int> rockPlacementIndexes(grid[0].length(), 0);
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].length(); j++) {
            if (grid[i][j] == 'O') {
                total += (grid.size() - rockPlacementIndexes[j]);
                rockPlacementIndexes[j]++;
            }
            if (grid[i][j] == '#') {
                rockPlacementIndexes[j] = i + 1;
            }
        }
    }

    cout << total << endl;
}