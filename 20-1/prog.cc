#include <iostream>
#include <queue>
#include <tuple>
#include "node.h"

using namespace std;

const int PUSHSES = 1000;

vector<string> explode(string s, char c);
string trim(string s);
int cacheCheck(long long entry, vector<tuple<long long, long long, long long>>& cache);
long long cacheEntry(vector<flipFlop*>& flipFlops);

int main() {
    unordered_map<string, node*> nodes;
    vector<flipFlop*> flipFlops;
    vector<con*> conjunctions;

    string s;
    string garbage;
    string list;
    while (cin >> s) {
        node* n;
        if (s == "broadcaster") {
            n = new broadcaster();
        } else if (s[0] == '%') {
            flipFlop* f = new flipFlop();
            n = f;
            s = s.substr(1);
            flipFlops.push_back(f);
        } else if (s[0] == '&') {
            con* c = new con();
            n = c;
            s = s.substr(1);
            conjunctions.push_back(c);
        }
        n->name = s;
        cin >> garbage;
        getline(cin, list);

        n->targets = explode(list, ',');

        nodes[s] = n;
    }

    // Now we need to wire up all the conjunctions
    for (int i = 0; i < conjunctions.size(); i++) {
        for (const auto n : nodes) {
            for (int j = 0; j < n.second->targets.size(); j++) {
                if (n.second->targets[j] == conjunctions[i]->name) {
                    conjunctions[i]->state[n.second->name] = false;
                    break;
                }
            }
        } 
    }

    long long lowC = 0;
    long long highC = 0;

    vector<tuple<long long, long long, long long>> cache;
    cache.push_back(make_tuple(0,0,0));

    for (int i = 1; i <= PUSHSES; i++) {
        queue<tuple<string, string, bool>> q;
        q.push(make_tuple("", "broadcaster", false));

        while (!q.empty()) {
            string sender = get<0>(q.front());
            string target = get<1>(q.front());
            bool high = get<2>(q.front());
            q.pop();

            if (high) {
                highC++;
            } else {
                lowC++;
            }

            if (nodes.count(target) > 0) {
                pair<bool, vector<string>> results = nodes[target]->sendSignal(high, sender);
                for (int j = 0; j < results.second.size(); j++) {
                    q.push(make_tuple(target, results.second[j], results.first));
                }
            }
        }
        long long entry = cacheEntry(flipFlops);
        int cacheFound = cacheCheck(entry, cache);
        if (cacheFound != -1) {
            cout << "Found loop starting at index " << cacheFound << "! I pushed the button to find this " << i << " times. This is a loop length of " << i - cacheFound << endl;
            int loopLength = i - cacheFound;
            int remaining = PUSHSES - i;
            int cyclesPossible = remaining / loopLength;
            int remainder = remaining % loopLength;
            lowC *= cyclesPossible + 1;
            highC *= cyclesPossible + 1;
            lowC += (get<1>(cache[cacheFound + remainder]) - get<1>(cache[cacheFound]));
            highC += (get<2>(cache[cacheFound + remainder]) - get<2>(cache[cacheFound]));
            break;
        } else {
            cache.push_back(make_tuple(entry, lowC, highC));
        }
    }

    cout << lowC * highC << endl;
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

int cacheCheck(long long entry, vector<tuple<long long, long long, long long>>& cache) {
    for (int i = 0; i < cache.size(); i++) {
        if (get<0>(cache[i]) == entry) {
            return i;
        }
    }
    return -1;
}

long long cacheEntry(vector<flipFlop*>& flipFlops) {
    long long entry = 0;
    for (int i = 0; i < flipFlops.size(); i++) {
        entry = entry << 1;
        if (flipFlops[i]->state) {
            entry++;
        }
    }

    return entry;
}