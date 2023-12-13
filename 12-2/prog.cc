#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

vector<int> splitNumbers(string s);
long long assignmentsPossible(string springs, vector<int> groups, int minSpacesNeededToSatisfyGroups, vector<pair<pair<string, vector<int>>, long long>>& cache);
long long valueFromCache(string s, vector<int>& groups, vector<pair<pair<string, vector<int>>, long long>>& cache);

int main() {
    string springs;
    string groupString;
    long long total = 0;
    while (cin >> springs) {
        vector<int> groups;
        int group;
        int minSpacesNeededToSatisfyGroups = 0;
        getline(cin, groupString);
        groups = splitNumbers(groupString);
        for (int i = 0; i < groups.size(); i++) {
            minSpacesNeededToSatisfyGroups += groups[i];
        }
        springs = springs + '?' + springs + '?' + springs + '?' + springs + '?' + springs;
        vector<int> unfoldedGroups;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < groups.size(); j++) {
                unfoldedGroups.push_back(groups[j]);
            }
        }
        minSpacesNeededToSatisfyGroups *= 5;
        vector<pair<pair<string, vector<int>>, long long>> cache;
        total += assignmentsPossible(springs, unfoldedGroups, minSpacesNeededToSatisfyGroups + (unfoldedGroups.size() - 1), cache);
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

long long assignmentsPossible(string springs, vector<int> groups, int minSpacesNeededToSatisfyGroups, vector<pair<pair<string, vector<int>>, long long>>& cache) {
    int i = 0;
    long long fromCache = valueFromCache(springs, groups, cache);
    if (fromCache == -1) {
        long long total = 0;
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
                        total += assignmentsPossible(springs.substr(i + groups[0] + 1), vector<int>(groups.begin() + 1, groups.end()), minSpacesNeededToSatisfyGroups - (1 + groups[0]), cache);
                    }
                }
            }
            if (springs[i] == '#') {
                break;
            }
            i++;
        }
        cache.push_back(make_pair(make_pair(springs, groups), total));
        return total;
    } else {
        return fromCache;
    }
}
long long valueFromCache(string s, vector<int>& groups, vector<pair<pair<string, vector<int>>, long long>>& cache) {
    for (int i = 0; i < cache.size(); i++) {
        if (cache[i].first.first == s) {
            if (groups.size() != cache[i].first.second.size()) {
                continue;
            }
            bool matches = true;
            for (int j = 0; j < cache[i].first.second.size(); j++) {
                if (cache[i].first.second[j] != groups[j]) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                return cache[i].second;
            }
        }
    }
    return -1;
}