#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> splitNumbers(string s);

int main() {
    string garbage;
    cin >> garbage; // Time:

    string timesString;
    getline(cin, timesString);
    vector<int> times = splitNumbers(timesString);

    cin >> garbage; // Distance:
    string distancesString;
    getline(cin, distancesString);
    vector<int> distances = splitNumbers(distancesString);

    int total = 1;

    for (int i = 0; i < times.size(); i++) {
        for (int j = 1; j < times[i]; j++) {
            if (j * (times[i] - j) > distances[i]) {
                total *= ((times[i] + 1) - (2 * j));
                break;
            }
        }
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
    }

    return i;
}