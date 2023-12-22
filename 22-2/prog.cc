#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

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

    brick() {}

    brick(const brick& other) {
        sX = other.sX;
        sY = other.sY;
        sZ = other.sZ;
        eX = other.eX;
        eY = other.eY;
        eZ = other.eZ;
        index = other.index;
    }
};

vector<string> explode(string s, char c);
vector<brick> copyBricks(vector<brick>& oldBricks, int ignore);
int settleBricks(vector<brick>& bricks);

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

    settleBricks(bricks);

    int total = 0;

    // For each brick, assume that brick wasn't there, and settle bricks again. How many bricks would move each time?
    for (int i = 0; i < bricks.size(); i++) {
        vector<brick> bricksWithOneRemoved = copyBricks(bricks, i);
        total += settleBricks(bricksWithOneRemoved);
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

vector<brick> copyBricks(vector<brick>& oldBricks, int ignore) {
    vector<brick> newBricks;
    for (int i = 0; i < oldBricks.size(); i++) {
        if (i != ignore) {
            newBricks.push_back(brick(oldBricks[i]));
        }
    }
    return newBricks;
}

int settleBricks(vector<brick>& bricks) {
    int bricksMoved = 0;

    vector<vector<vector<int>>> grid(10, vector<vector<int>>(10, vector<int>(400, -1)));

    sort(bricks.begin(), bricks.end());

    // Settle the bricks down
    for (int i = 0; i < bricks.size(); i++) {
        int curZ = bricks[i].sZ;
        bool canMoveDown = true;
        bool actuallyMoved = false;
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
            if (canMoveDown) {
                curZ--;
                actuallyMoved = true;
            }
        }
        if (actuallyMoved) bricksMoved++;
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
    return bricksMoved;
}