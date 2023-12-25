#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

pair<int, int> singleIndexToRowAndColumn(int index, int columnSize);
vector<string> explode(string s, char c);
string trim(string s);
vector<int> bfs(vector<vector<bool>>& grid, int start, int end);
int bfsCount(vector<vector<bool>>& grid);

int main() {
    string line;
    int index = 0;
    vector<vector<bool>> map;
    unordered_map<string, int> indexMap;

    while (getline(cin, line)) {
        vector<string> results1 = explode(line, ':');
        string source = results1[0];
        vector<string> results2 = explode(results1[1], ' ');

        if (indexMap.count(source) == 0) {
            indexMap[source] = index;
            map.push_back(vector<bool>(map.size()));
            for (int i = 0; i < map.size(); i++) map[i].push_back(false);
            index++;
        }

        for (int i = 0; i < results2.size(); i++) {
            if (indexMap.count(results2[i]) == 0) {
                indexMap[results2[i]] = index;
                map.push_back(vector<bool>(map.size()));
                for (int i = 0; i < map.size(); i++) map[i].push_back(false);
                index++;
            }
            map[indexMap[source]][indexMap[results2[i]]] = true;
        }
    }

    int columnSize = map[0].size();

    // Compare the first node to each other node
    // Find the shortest path 3 times, removing that path each time
    // Try to find the shortest path a 4th time
    // If the two nodes are in the same component, this will succeed
    // Otherwise, it will fail
    // If it fails, we have already cut the 3 paths (and some other ones)
    // Perform a count of all reachable nodes from first node
    // Multiply this count by (fullCount - count) and return
    for (int i = 1; i < map.size(); i++) {
        // Copy the map so we can modify it temporarily
        vector<vector<bool>> tempMap;
        for (int j = 0; j < map.size(); j++) {
            tempMap.push_back(vector<bool>(map[j].begin(), map[j].end()));
        }

        // Search 1
        vector<int> path1 = bfs(tempMap, 0, i);
        for (int j = 0; j < path1.size() - 1; j++) {
            tempMap[path1[j]][path1[j+1]] = false;
            tempMap[path1[j+1]][path1[j]] = false;
        }

        // Search 2
        vector<int> path2 = bfs(tempMap, 0, i);
        for (int j = 0; j < path2.size() - 1; j++) {
            tempMap[path2[j]][path2[j+1]] = false;
            tempMap[path2[j+1]][path2[j]] = false;
        }

        // Search 3
        vector<int> path3 = bfs(tempMap, 0, i);
        for (int j = 0; j < path3.size() - 1; j++) {
            tempMap[path3[j]][path3[j+1]] = false;
            tempMap[path3[j+1]][path3[j]] = false;
        }

        // Search 4 (the big one)
        vector<int> path4 = bfs(tempMap, 0, i);
        if (path4.size() == 0) {
            // This is the one
            int firstComponentCount = bfsCount(tempMap);
            cout << firstComponentCount * (map.size() - firstComponentCount) << endl;
            break;
        }
    }
}

pair<int, int> singleIndexToRowAndColumn(int index, int columnSize) {
    return make_pair(index / columnSize, index % columnSize);
}

vector<string> explode(string s, char c) {
    vector<string> results;
    string buffer = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            results.push_back(trim(buffer));
            buffer = "";
        } else {
            buffer += s[i];
        }
    }

    results.push_back(trim(buffer));
    return results;
}

string trim(string s) {
    int left = 0, right = s.length() - 1;

    for (int i = 0; i < s.length() && s[i] == ' '; i++) {
        left++;
    }

    for (int i = s.length() - 1; i >= 0 && s[i] == ' '; i--) {
        right--;
    }

    if (left > right) return "";
    return s.substr(left, right - left + 1);
}

// Return empty vector if no path
vector<int> bfs(vector<vector<bool>>& grid, int start, int end) {
    vector<bool> visited(grid.size(), false);
    unordered_map<int, int> path;
    path[start] = -1;
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int index = q.front();
        if (index == end) break;
        q.pop();
        for (int i = 0; i < grid[index].size(); i++) {
            if ((grid[index][i] || grid[i][index]) && !visited[i]) {
                visited[i] = true;
                path[i] = index;
                q.push(i);
            }
        }
    }

    if (path.count(end) == 0) {
        return vector<int>();
    }

    vector<int> pathTaken;
    int at = end;
    while (at != -1) {
        pathTaken.push_back(at);
        at = path[at];
    }
    
    reverse(pathTaken.begin(), pathTaken.end());
    return pathTaken;
}

int bfsCount(vector<vector<bool>>& grid) {
    vector<bool> visited(grid.size(), false);
    queue<int> q;
    q.push(0);
    int count = 1;
    visited[0] = true;

    while (!q.empty()) {
        int index = q.front();
        q.pop();

        for (int i = 0; i < grid[index].size(); i++) {
            if ((grid[index][i] || grid[i][index]) && !visited[i]) {
                visited[i] = true;
                count++;
                q.push(i);
            }
        }
    }

    return count;
}