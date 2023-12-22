#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> explode(string s, char c);

struct brick {
    int sX;
    int sY;
    int sZ;
    int eX;
    int eY;
    int eZ;
    int index;

    bool operator<(const brick other) {
        return sZ < other.sZ;
    }
};

int main() {
    string line;
    int index = 0;
    vector<brick> bricks;

    while (getline(cin, line)) {
        vector<string> results1 = explode(line, '~');
        vector<string> resultsS = explode(results1[0], ',');
        vector<string> resultsE = explode(results1[1], ',');
        brick newBrick;
        newBrick.sX = stoi(resultsS[0]);
        newBrick.sY = stoi(resultsS[1]);
        newBrick.sZ = stoi(resultsS[2]);
        newBrick.eX = stoi(resultsE[0]);
        newBrick.eY = stoi(resultsE[1]);
        newBrick.eZ = stoi(resultsE[2]);
        newBrick.index = index;

        bricks.push_back(newBrick);
        index++;
    }

    vector<vector<vector<int>>> grid(10, vector<vector<int>>(10, vector<int>(400, -1)));
    unordered_map<int, int> supportCounts;

    sort(bricks.begin(), bricks.end());

    // Settle the bricks down
    for (int i = 0; i < bricks.size(); i++) {
        int curZ = bricks[i].sZ;
        bool canMoveDown = true;
        unordered_map<int, bool> supports;
        while (curZ > 1 && canMoveDown) {
            for (int x = bricks[i].sX; x <= bricks[i].eX; x++) {
                for (int y = bricks[i].sY; y <= bricks[i].eY; y++) {
                    if (grid[x][y][curZ - 1] != -1) {
                        supports[grid[x][y][curZ - 1]] = true;
                        canMoveDown = false;
                    }
                }
            }
            if (canMoveDown) curZ--;
        }
        supportCounts[bricks[i].index] = supports.size();
        bricks[i].eZ = curZ + (bricks[i].eZ - bricks[i].sZ);
        bricks[i].sZ = curZ;
        for (int x = bricks[i].sX; x <= bricks[i].eX; x++) {
            for (int y = bricks[i].sY; y <= bricks[i].eY; y++) {
                for (int z = bricks[i].sZ; z <= bricks[i].eZ; z++) {
                    grid[x][y][z] = bricks[i].index;
                }
            }
        }
    }

    int total = 0;
    // Should be settled down now. 
    // For each brick, look at all bricks immediately above it. 
    // If any brick is supported by only one brick (this one), we can't remove this brick

    for (int i = 0; i < bricks.size(); i++) {
        bool canRemove = true;

        for (int x = bricks[i].sX; x <= bricks[i].eX && canRemove; x++) {
            for (int y = bricks[i].sY; y <= bricks[i].eY && canRemove; y++) {
                if (grid[x][y][bricks[i].eZ + 1] != -1) {
                    canRemove = supportCounts[grid[x][y][bricks[i].eZ + 1]] > 1;
                }
            }
        }

        if (canRemove) total++;
    }

    cout << total << endl;
}

vector<string> explode(string s, char c) {
    vector<string> results;
    string buffer = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            results.push_back(buffer);
            buffer = "";
        } else {
            buffer += s[i];
        }
    }

    results.push_back(buffer);
    return results;
}