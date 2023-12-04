#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main() {
    string garbage;
    string winningNumber;
    unordered_map<int, bool> winningNumbers;
    unordered_map<int, int> cardCount;

    int total = 0;
    int cardNumber;
    int cardMatches;

    while (cin >> garbage) { // Card

        cardMatches = 0;
        cin >> cardNumber; // #
        cin >> garbage; // :

        int thisCardCount = 1;
        if (cardCount.count(cardNumber)) {
            thisCardCount = cardCount[cardNumber];
        }

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
                cardMatches++;
            }
        }

        for (int i = 1; i <= cardMatches; i++) {
            if (cardCount.count(cardNumber + i)) {
                cardCount[cardNumber + i] += thisCardCount;
            } else {
                cardCount[cardNumber + i] = thisCardCount + 1;
            }
        }

        total += thisCardCount;
    }

    cout << total << endl;
}