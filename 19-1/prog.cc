#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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
bool checkPart(instruction i, part p);

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

    while (getline(cin, line)) {
        line = line.substr(1, line.length() - 2);

        vector<string> traits = explode(line, ',');
        part newPart;
        newPart.x = stoll(traits[0].substr(2));
        newPart.m = stoll(traits[1].substr(2));
        newPart.a = stoll(traits[2].substr(2));
        newPart.s = stoll(traits[3].substr(2));
        parts.push_back(newPart);
    }

    long long total = 0;
    for (int i = 0; i < parts.size(); i++) {
        bool accepted = false;
        bool rejected = false;
        instructions curInstructions = map["in"];

        while (!accepted && !rejected) {
            string newNode = "";
            for (int j = 0; j < curInstructions.list.size(); j++) {
                if (checkPart(curInstructions.list[j], parts[i])) {
                    newNode = curInstructions.list[j].target;
                    break;
                }
            }
            if (newNode.empty()) {
                newNode = curInstructions.fallback;
            }
            if (newNode == "A") {
                accepted = true;
            } else if (newNode == "R") {
                rejected = true;
            } else {
                curInstructions = map[newNode];
            }
        }

        if (accepted) {
            total += parts[i].x + parts[i].m + parts[i].a + parts[i].s;
        } 
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

bool checkPart(instruction i, part p) {
    int valueToCheck;

    switch (i.trait) {
        case 'x':
            valueToCheck = p.x;
            break;
        case 'm':
            valueToCheck = p.m;
            break;
        case 'a':
            valueToCheck = p.a;
            break;
        case 's':
            valueToCheck = p.s;
            break;
    }

    if (i.comparison == '<') {
        return valueToCheck < i.value;
    } else {
        return valueToCheck > i.value;
    }
}