#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

const long long UNIVERSE_EXPANSION_MULTIPLE = 1000000;

int main() {
    vector<bool> rowsAreEmpty;
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
        rowsAreEmpty.push_back(!hasGalaxy);
    }
    
    vector<pair<long long, long long>> galaxies;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '#') {
                galaxies.push_back(make_pair(i, j));
            }
        }
    }

    long long total = 0;

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            for (int row = min(galaxies[i].first, galaxies[j].first) + 1; row <= max(galaxies[i].first, galaxies[j].first); row++) {
                if (rowsAreEmpty[row]) {
                    total += UNIVERSE_EXPANSION_MULTIPLE;
                } else {
                    total += 1;
                }
            }
            for (int column = min(galaxies[i].second, galaxies[j].second) + 1; column <= max(galaxies[i].second, galaxies[j].second); column++) {
                if (columnsAreEmpty[column]) {
                    total += UNIVERSE_EXPANSION_MULTIPLE;
                } else {
                    total += 1;
                }
            }
        }
    }

    cout << total << endl;
}