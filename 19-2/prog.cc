#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

struct instruction {
    char trait;
    char comparison;
    long long value;
    string target;
};

struct instructions {
    vector<instruction> list;
    string fallback;
};

struct part {
    long long x;
    long long m;
    long long a;
    long long s;
};

vector<string> explode(string s, char c);
long long traverse(string node, long long minx, long long minm, long long mina, long long mins,
                                        long long maxx, long long maxm, long long maxa, long long maxs,
                                        unordered_map<string, instructions>& map);

int main() {
    string line;
    unordered_map<string, instructions> map;

    while (getline(cin, line) && !line.empty()) {
        vector<string> results1 = explode(line, '{');
        string name = results1[0];
        string rest1 = results1[1];
        rest1 = rest1.substr(0, rest1.length() - 1);

        vector<string> results2 = explode(rest1, ',');
        vector<instruction> in;
        for (int i = 0; i < results2.size() - 1; i++) {
            vector<string> results3 = explode(results2[i], ':');
            instruction newIn;
            newIn.trait = results3[0][0];
            newIn.comparison = results3[0][1];
            newIn.value = stoll(results3[0].substr(2));
            newIn.target = results3[1];
            in.push_back(newIn);
        }
        instructions newIns;
        newIns.fallback = results2[results2.size() - 1];
        newIns.list = in;
        map[name] = newIns;
    }

    vector<part> parts;

    cout << traverse("in", 1, 1, 1, 1, 4000, 4000, 4000, 4000, map) << endl;
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

long long traverse(string node, long long minx, long long minm, long long mina, long long mins,
                                        long long maxx, long long maxm, long long maxa, long long maxs,
                                        unordered_map<string, instructions>& map) {
    
    if (node == "R") {
        return 0;
    } 
    if (node == "A") {
        return (maxx - minx + 1) * (maxm - minm + 1) * (maxa - mina + 1) * (maxs - mins + 1);
    }
    long long total = 0;
    instructions in = map[node];
    for (int i = 0; i < in.list.size(); i++) {
        if (in.list[i].comparison == '>') {
            switch (in.list[i].trait) {
                case 'x':
                    total += traverse(in.list[i].target, max(in.list[i].value + 1, minx), minm, mina, mins, maxx, maxm, maxa, maxs, map);
                    maxx = min(in.list[i].value, maxx);
                    break;
                case 'm':
                    total += traverse(in.list[i].target, minx, max(in.list[i].value + 1, minm), mina, mins, maxx, maxm, maxa, maxs, map);
                    maxm = min(in.list[i].value, maxm);
                    break;
                case 'a':
                    total += traverse(in.list[i].target, minx, minm, max(in.list[i].value + 1, mina), mins, maxx, maxm, maxa, maxs, map);
                    maxa = min(in.list[i].value, maxa);
                    break;
                case 's':
                    total += traverse(in.list[i].target, minx, minm, mina, max(in.list[i].value + 1, mins), maxx, maxm, maxa, maxs, map);
                    maxs = min(in.list[i].value, maxs);
                    break;
            }
        } else {
            switch (in.list[i].trait) {
                case 'x':
                    total += traverse(in.list[i].target, minx, minm, mina, mins, min(in.list[i].value - 1, maxx), maxm, maxa, maxs, map);
                    minx = max(in.list[i].value, minx);
                    break;
                case 'm':
                    total += traverse(in.list[i].target, minx, minm, mina, mins, maxx, min(in.list[i].value - 1, maxm), maxa, maxs, map);
                    minm = max(in.list[i].value, minm);
                    break;
                case 'a':
                    total += traverse(in.list[i].target, minx, minm, mina, mins, maxx, maxm, min(in.list[i].value - 1, maxa), maxs, map);
                    mina = max(in.list[i].value, mina);
                    break;
                case 's':
                    total += traverse(in.list[i].target, minx, minm, mina, mins, maxx, maxm, maxa, min(in.list[i].value - 1, maxs), map);
                    mins = max(in.list[i].value, mins);
                    break;
            }
        }
    }
    total += traverse(in.fallback, minx, minm, mina, mins, maxx, maxm, maxa, maxs, map);
    return total;
}