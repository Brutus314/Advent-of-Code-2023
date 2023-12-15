#include <iostream>
#include <string>
#include <vector>

using namespace std;

void cycle(vector<string>& grid);
void moveNorth(vector<string>& grid);
void moveWest(vector<string>& grid);
void moveSouth(vector<string>& grid);
void moveEast(vector<string>& grid);
long long cacheCompare(vector<vector<string>>& cache, vector<string>& grid);
int load(vector<string>& grid);

int main() {
    vector<string> grid;
    string line;

    while (getline(cin, line)) {
        grid.push_back(line);
    }

    vector<vector<string>> cache;
    for (long long i = 0; i < 1000000000; i++) {
        cycle(grid);
        long long cacheIndex = cacheCompare(cache, grid);
        if (cacheIndex != -1) {
            long long loopLength = i - cacheIndex;
            grid = cache[cacheIndex + ((1000000000 - (i + 1)) % loopLength)];
            i = 1000000001;
        } else {
            cache.push_back(vector<string>(grid.begin(), grid.end()));
        }
    }

    cout << load(grid) << endl;
}

void cycle(vector<string>& grid) {
    moveNorth(grid);
    moveWest(grid);
    moveSouth(grid);
    moveEast(grid);
}

void moveNorth(vector<string>& grid) {
    vector<int> rockPlacementIndexes(grid[0].length(), 0);
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].length(); j++) {
            if (grid[i][j] == 'O') {
                grid[i][j] = '.';
                grid[rockPlacementIndexes[j]][j] = 'O';
                rockPlacementIndexes[j]++;
            }
            if (grid[i][j] == '#') {
                rockPlacementIndexes[j] = i + 1;
            }
        }
    }
}

void moveWest(vector<string>& grid) {
    vector<int> rockPlacementIndexes(grid.size(), 0);
    for (int i = 0; i < grid[0].length(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[j][i] == 'O') {
                grid[j][i] = '.';
                grid[j][rockPlacementIndexes[j]] = 'O';
                rockPlacementIndexes[j]++;
            }
            if (grid[j][i] == '#') {
                rockPlacementIndexes[j] = i + 1;
            }
        }
    }
}

void moveSouth(vector<string>& grid) {
    vector<int> rockPlacementIndexes(grid[0].length(), grid.size() - 1);
    for (int i = grid.size() - 1; i >= 0; i--) {
        for (int j = 0; j < grid[i].length(); j++) {
            if (grid[i][j] == 'O') {
                grid[i][j] = '.';
                grid[rockPlacementIndexes[j]][j] = 'O';
                rockPlacementIndexes[j]--;
            }
            if (grid[i][j] == '#') {
                rockPlacementIndexes[j] = i - 1;
            }
        }
    }
}

void moveEast(vector<string>& grid) {
    vector<int> rockPlacementIndexes(grid.size(), grid[0].length() - 1);
    for (int i = grid[0].length() - 1; i >= 0; i--) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[j][i] == 'O') {
                grid[j][i] = '.';
                grid[j][rockPlacementIndexes[j]] = 'O';
                rockPlacementIndexes[j]--;
            }
            if (grid[j][i] == '#') {
                rockPlacementIndexes[j] = i - 1;
            }
        }
    }
}

long long cacheCompare(vector<vector<string>>& cache, vector<string>& grid) {
    for (int i = 0; i < cache.size(); i++) {
        bool same = true;
        for (int j = 0; j < cache[i].size(); j++) {
            if (cache[i][j] != grid[j]) {
                same = false;
                break;
            }
        }
        if (same) {
            return i;
        }
    }
    return -1;
}

int load(vector<string>& grid) {
    int total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                total += (grid.size() - i);
            }
        }
    }
    return total;
}