#include <iostream>
#include <queue>
#include <tuple>
#include <numeric>
#include "node.h"

using namespace std;

vector<string> explode(string s, char c);
string trim(string s);

int main() {
    unordered_map<string, node*> nodes;
    vector<flipFlop*> flipFlops;
    vector<con*> conjunctions;

    string rxPointer;

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

        if (n->targets.size() == 1 && n->targets[0] == "rx") {
            rxPointer = s;
        }

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

    unordered_map<string, long long> feedMap;

    for (int i = 0; i < conjunctions.size(); i++) {
        if (conjunctions[i]->targets.size() == 1 && conjunctions[i]->targets[0] == rxPointer) {
            feedMap[conjunctions[i]->name] = -1;
        }
    }

    int pushes = 0;

    while (true) {
        queue<tuple<string, string, bool>> q;
        q.push(make_tuple("", "broadcaster", false));
        pushes++;
        bool started = false;
        while (!q.empty()) {
            string sender = get<0>(q.front());
            string target = get<1>(q.front());
            bool high = get<2>(q.front());
            q.pop();

            if (nodes.count(target) > 0) {

                if (high && feedMap.count(sender) > 0 && feedMap[sender] == -1) {
                    feedMap[sender] = pushes;
                    bool couldStart = true;
                    for (const auto n : feedMap) {
                        if (n.second == -1) {
                            couldStart = false;
                            break;
                        };
                    }
                    if (couldStart) {
                        started = true;
                        break;   
                    }
                }

                pair<bool, vector<string>> results = nodes[target]->sendSignal(high, sender);
                for (int j = 0; j < results.second.size(); j++) {
                    q.push(make_tuple(target, results.second[j], results.first));
                }
            }
        }
        if (started) break;
    }

    long long total = 1;
    for (const auto n : feedMap) {
        total = lcm(total, n.second);
    }

    std::cout << total << endl;
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