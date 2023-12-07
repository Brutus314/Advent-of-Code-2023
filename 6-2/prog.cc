#include <iostream>
#include <string>
#include <cctype>

using namespace std;

long long combineNumbers(string s);

int main() {
    string garbage;
    cin >> garbage; // Time:

    string timesString;
    getline(cin, timesString);
    long long time = combineNumbers(timesString);

    cin >> garbage; // Distance:
    string distancesString;
    getline(cin, distancesString);
    long long distance = combineNumbers(distancesString);

    long long leftBound = 1;
    long long rightBound = time - 1;

    while (leftBound <= rightBound) {
        long long middle = (leftBound + rightBound) / 2;

        if (middle * (time - middle) > distance) {
            rightBound = middle - 1;
        } else {
            leftBound = middle + 1;
        }
    }

    cout << ((time + 1) - (2 * leftBound)) << endl;
}

long long combineNumbers(string s) {
    string newString = "";

    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i])) {
            newString += s[i];
        }
    }

    return stoll(newString);
}