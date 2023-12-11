#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

int main() {
    vector<bool> columnsAreEmpty;
    vector<string> grid;
    string line;

    while (getline(cin, line)) {
        if (columnsAreEmpty.size() == 0) {
            columnsAreEmpty = vector<bool>(line.length(), true);
        }

        bool hasGalaxy = false;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '#') {
                columnsAreEmpty[i] = false;
                hasGalaxy = true;
            }
        }

        grid.push_back(line);
        if (!hasGalaxy) {
            grid.push_back(line);
        }
    }

    for (int i = columnsAreEmpty.size() - 1; i >= 0; i--) {
        if (columnsAreEmpty[i]) {
            for (int j = 0; j < grid.size(); j++) {
                grid[j] = grid[j].substr(0, i) + '.' + grid[j].substr(i);
            }
        }
    }
    
    vector<pair<int, int>> galaxies;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '#') {
                galaxies.push_back(make_pair(i, j));
            }
        }
    }

    int total = 0;

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            total += (abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second));
        }
    }

    cout << total << endl;
}