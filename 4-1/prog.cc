#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main() {
    string garbage;
    string winningNumber;
    unordered_map<int, bool> winningNumbers;

    int total = 0;
    int cardTotal;

    while (cin >> garbage) { // Card
        cardTotal = 0;
        cin >> garbage; // #:

        winningNumbers.clear();
        cin >> winningNumber;
        while (winningNumber != "|") {
            winningNumbers[stoi(winningNumber)] = true;
            cin >> winningNumber;
        }

        stringstream myNumbers;
        string rest;
        getline(cin, rest);
        myNumbers << rest;

        int myNumber;
        while (myNumbers >> myNumber) {
            if (winningNumbers.count(myNumber)) {
                if (cardTotal == 0) {
                    cardTotal = 1;
                } else {
                    cardTotal *= 2;
                }
            }
        }

        total += cardTotal;
    }

    cout << total << endl;
}