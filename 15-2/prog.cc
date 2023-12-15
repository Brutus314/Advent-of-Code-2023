#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

int getInstructionHash(string instruction, unordered_map<string, int>& cache);
bool instructionIsAdd(string instruction);
vector<string> explode(string s, char c);

int main() {
    int total = 0;
    string buffer = "";
    string line;
    getline(cin, line);
    vector<string> instructions = explode(line, ',');

    unordered_map<string, int> mapCache;
    unordered_map<string, int> indexMap;

    vector<vector<pair<string, int>>> boxes(256, vector<pair<string, int>>());

    for (int i = 0; i < instructions.size(); i++) {
        int hash = getInstructionHash(instructions[i], mapCache);

        if (instructionIsAdd(instructions[i])) {
            vector<string> parts = explode(instructions[i], '=');
            string path = parts[0];
            int lens = stoi(parts[1]);

            if (indexMap.count(path) == 0 || indexMap[path] == -1) {
                indexMap[path] = boxes[hash].size();
                boxes[hash].push_back(make_pair(path, lens));
            } else {
                boxes[hash][indexMap[path]].second = lens;
            }
        } else {
            string path = instructions[i].substr(0, instructions[i].length() - 1);

            if (indexMap.count(path) && indexMap[path] != -1) {
                boxes[hash].erase(boxes[hash].begin() + indexMap[path], boxes[hash].begin() + indexMap[path] + 1);
                for (int i = indexMap[path]; i < boxes[hash].size(); i++) {
                    indexMap[boxes[hash][i].first] = i;
                }
                indexMap[path] = -1;
            }
        }
    }

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            total += (i + 1) * (j + 1) * (boxes[i][j].second);
        }
    }

    cout << total << endl;;
}

int getInstructionHash(string instruction, unordered_map<string, int>& cache) {
    if (cache.count(instruction)) {
        return cache.at(instruction);
    }

    int index = 0;
    int hash = 0;
    while (instruction[index] != '-' && instruction[index] != '=') {
        hash += instruction[index];
        hash *= 17;
        hash %= 256;
        index++;
    }

    cache[instruction] = hash;
    return hash;
}

bool instructionIsAdd(string instruction) {
    if (instruction.find('=') != -1) {
        return true;
    } else {
        return false;
    }
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