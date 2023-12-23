#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <cmath>

using namespace std;

int rowAndColumnToSingleIndex(int row, int column, int columnSize);
vector<vector<int>> parseIntoGrid(vector<string>& grid);
int traverseNodeGrid(vector<vector<int>>& grid, int curNode, vector<bool>& visited);

int main() {
    vector<string> grid;
    string line;

    while (getline(cin, line)) {
        grid.push_back(line);
    }
    int columnSize = grid[0].length();

    unordered_map<int, int> longestPathAtJunctions;
    vector<vector<int>> nodeGrid = parseIntoGrid(grid);
    vector<bool> visited(nodeGrid.size(), false);
    
    cout << traverseNodeGrid(nodeGrid, 0, visited) << endl;
}

int rowAndColumnToSingleIndex(int row, int column, int columnSize) {
    return (row * columnSize) + column;
}

vector<vector<int>> parseIntoGrid(vector<string>& grid) {
    vector<vector<int>> nodeGrid(36, vector<int>(36, -1)); // My input had 34 junctions, plus the start and end points
    unordered_map<int, int> junctionIndexMap;
    queue<int> q;
    junctionIndexMap[1] = 0; // Start point counts as a node
    junctionIndexMap[rowAndColumnToSingleIndex(grid.size() - 1, grid[0].length() - 2, grid[0].length())] = 1; // End point counts as a node

    int curIndex = 2;
    q.push(rowAndColumnToSingleIndex(0, 1, grid[0].length()));

    while (!q.empty()) {
        int rowAndColumn = q.front();
        int row = rowAndColumn / grid[0].length();
        int column = rowAndColumn % grid[0].length();
        q.pop();

        queue<pair<int, int>> q2;
        vector<bool> seens(grid.size() * grid[0].length(), false);
        seens[rowAndColumn] = true;
        q2.push(make_pair(rowAndColumnToSingleIndex(row - 1, column, grid[0].length()), 0));
        q2.push(make_pair(rowAndColumnToSingleIndex(row + 1, column, grid[0].length()), 0));
        q2.push(make_pair(rowAndColumnToSingleIndex(row, column - 1, grid[0].length()), 0));
        q2.push(make_pair(rowAndColumnToSingleIndex(row, column + 1, grid[0].length()), 0));

        while (!q2.empty()) {
            int curRowAndColumn = q2.front().first;
            int curRow = curRowAndColumn / grid[0].length();
            int curColumn = curRowAndColumn % grid[0].length();
            int distance = q2.front().second;
            q2.pop();

            if (curRowAndColumn <= 0 || curRow < 0 || curColumn < 0 || curRow >= grid.size() || curColumn >= grid[0].length() || grid[curRow][curColumn] == '#') {
                // Off the grid, or is a rock
                continue;
            }

            distance++;

            if (curRow == grid.size() - 1 && curColumn == grid[0].length() - 2) {
                // Reached the end
                nodeGrid[junctionIndexMap[rowAndColumn]][1] = distance;
                continue;
            }

            seens[curRowAndColumn] = true;

            // How many paths are there?
            int pathsToTake = 0;
            bool canGoLeft = false, canGoRight = false, canGoUp = false, canGoDown = false;

            // Up
            if (curRow > 0 && !seens[rowAndColumnToSingleIndex(curRow - 1, curColumn, grid[0].length())] && grid[curRow - 1][curColumn] != '#') {
                pathsToTake++;
                canGoUp = true;
            }
            // Down
            if (curRow < grid.size() - 1 && !seens[rowAndColumnToSingleIndex(curRow + 1, curColumn, grid[0].length())] && grid[curRow + 1][curColumn] != '#') {
                pathsToTake++;
                canGoDown = true;
            }
            // Left
            if (curColumn > 0 && !seens[rowAndColumnToSingleIndex(curRow, curColumn - 1, grid[0].length())] && grid[curRow][curColumn - 1] != '#') {
                pathsToTake++;
                canGoLeft = true;
            }
            // Right
            if (curColumn < grid[0].length() - 1 && !seens[rowAndColumnToSingleIndex(curRow, curColumn + 1, grid[0].length())] && grid[curRow][curColumn + 1] != '#') {
                pathsToTake++;
                canGoRight= true;
            }

            if (pathsToTake == 0) continue;

            if (pathsToTake == 1) {
                // Not a junction
                if (canGoUp) {
                    q2.push(make_pair(rowAndColumnToSingleIndex(curRow - 1, curColumn, grid[0].length()), distance));
                }
                if (canGoDown) {
                    q2.push(make_pair(rowAndColumnToSingleIndex(curRow + 1, curColumn, grid[0].length()), distance));
                }
                if (canGoLeft) {
                    q2.push(make_pair(rowAndColumnToSingleIndex(curRow, curColumn - 1, grid[0].length()), distance));
                }
                if (canGoRight) {
                    q2.push(make_pair(rowAndColumnToSingleIndex(curRow, curColumn + 1, grid[0].length()), distance));
                }
                continue;
            } else {
                // We are at a junction. Log the path distance
                if (junctionIndexMap.count(rowAndColumnToSingleIndex(curRow, curColumn, grid[0].length()))) {
                    // We already made it to this junction. Just need to update paths
                    nodeGrid[junctionIndexMap[rowAndColumn]][junctionIndexMap[curRowAndColumn]] = distance;
                    continue;
                } else {
                    // Haven't seen this junction yet. Need to register its index
                    junctionIndexMap[curRowAndColumn] = curIndex;
                    nodeGrid[junctionIndexMap[rowAndColumn]][curIndex] = distance;
                    curIndex++;
                    q.push(curRowAndColumn);
                }
            }
        }
    }
    return nodeGrid;
}

int traverseNodeGrid(vector<vector<int>>& grid, int curNode, vector<bool>& visited) {
    visited[curNode] = true;
    int curMax = 0;

    for (int i = 0; i < grid[curNode].size(); i++) {
        if (grid[curNode][i] == -1) continue;
        if (visited[i]) continue;
        if (i == 1)  {
            visited[curNode] = false;
            return grid[curNode][i];
        }
        curMax = max(curMax, grid[curNode][i] + traverseNodeGrid(grid, i, visited));
    }
    
    visited[curNode] = false;

    if (curMax == 0) return INT32_MIN;

    return curMax;
}