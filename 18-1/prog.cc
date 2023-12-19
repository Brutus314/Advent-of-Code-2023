#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    char dir;
    int distance;
    string color;
    
    vector<vector<bool>> grid(1000, vector<bool>(1000, false));
    vector<vector<bool>> border(1000, vector<bool>(1000, false));
    int wLeft = 0, wRight = 0, hUp = 0, hDown = 0;
    int curWidth = 0, curHeight = 0;
    int row = 500, column = 500;

    while (cin >> dir) {
        cin >> distance;
        getline(cin, color);

        switch (dir) {
            case 'U':
                for (int i = 0; i < distance; i++) {
                    row--;
                    grid[row][column] = true;
                    border[row][column] = true;
                }
                break;
            case 'D':
                for (int i = 0; i < distance; i++) {
                    row++;
                    grid[row][column] = true;
                    border[row][column] = true;
                }
                break;
            case 'L':
                for (int i = 0; i < distance; i++) {
                    column--;
                    grid[row][column] = true;
                    border[row][column] = true;
                }
                break;
            case 'R':
                for (int i = 0; i < distance; i++) {
                    column++;
                    grid[row][column] = true;
                    border[row][column] = true;
                }
                break;
        }
    }
    
    int totalSpaces = grid.size() * grid[0].size();
    int outsideSpaces = 0;

    queue<pair<int, int>> spaces;
    spaces.push(make_pair(0, 0));

    while (!spaces.empty()) {
        int checkRow = spaces.front().first;
        int checkColumn = spaces.front().second;
        spaces.pop();

        if (checkRow < 0 || checkColumn < 0 || checkRow >= grid.size() || checkColumn >= grid[0].size()) {
            continue;
        }

        if (grid[checkRow][checkColumn]) {
            continue;
        }

        grid[checkRow][checkColumn] = true;
        outsideSpaces++;
        spaces.push(make_pair(checkRow - 1, checkColumn));
        spaces.push(make_pair(checkRow + 1, checkColumn));
        spaces.push(make_pair(checkRow, checkColumn - 1));
        spaces.push(make_pair(checkRow, checkColumn + 1));
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            cout << ((!grid[i][j] || border[i][j]) ? '#' : '.');
        }
        cout << endl;
    }

    cout << totalSpaces - outsideSpaces << endl;
    
}