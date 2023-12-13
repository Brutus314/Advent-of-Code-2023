#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> splitNumbers(string s);
int assignmentsPossible(string springs, vector<int> groups, int minSpacesNeededToSatisfyGroups);

int main() {
    string springs;
    string groupString;
    int total = 0;
    while (cin >> springs) {
        vector<int> groups;
        int group;
        int minSpacesNeededToSatisfyGroups = 0;
        getline(cin, groupString);
        groups = splitNumbers(groupString);
        for (int i = 0; i < groups.size(); i++) {
            minSpacesNeededToSatisfyGroups += groups[i];
        }

        total += assignmentsPossible(springs, groups, minSpacesNeededToSatisfyGroups + (groups.size() - 1));
    }

    cout << total << endl;
}

vector<int> splitNumbers(string s) {
    vector<int> i;
    int num;
    stringstream ss;

    ss << s;
    while (ss >> num) {
        i.push_back(num);
        ss.ignore();
    }

    return i;
}

int assignmentsPossible(string springs, vector<int> groups, int minSpacesNeededToSatisfyGroups) {
    int i = 0;
    int total = 0;
    while (springs.length() >= i + minSpacesNeededToSatisfyGroups) {
        if (springs[i] != '.') {
            bool canAddToGroup = true;
            for (int j = 0; j < groups[0]; j++) {
                if (springs[i + j] == '.') {
                    canAddToGroup = false;
                    break;
                }
            }
            if (canAddToGroup && (groups.size() == 1 || springs[i + groups[0]] != '#')) {
                // Can have this group here. Do the rest fit?
                if (groups.size() == 1) {
                    // It does, as long as no other # remain
                    bool otherSpringsExist = false;
                    for (int j = i + groups[0]; j < springs.length(); j++) {
                        if (springs[j] == '#') {
                            otherSpringsExist = true;
                            break;
                        }
                    }
                    if (!otherSpringsExist) {
                        total++;
                    }
                } else {
                    // Try to place the rest, and see how many possibilities there are with the sub string and sub group
                    total += assignmentsPossible(springs.substr(i + groups[0] + 1), vector<int>(groups.begin() + 1, groups.end()), minSpacesNeededToSatisfyGroups - (1 + groups[0]));
                }
            }
        }
        if (springs[i] == '#') {
            break;
        }
        i++;
    }
    return total;
}