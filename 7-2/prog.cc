#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "hand.hpp"

using namespace std;

int main() {
    string garbage;
    char card;
    int bid;
    vector<Hand> hands;

    while (cin >> card) {
        Hand newHand;
        newHand.addCard(card);
        cin >> card;
        newHand.addCard(card);
        cin >> card;
        newHand.addCard(card);
        cin >> card;
        newHand.addCard(card);
        cin >> card;
        newHand.addCard(card);

        cin >> bid;
        newHand.setBid(bid);
        hands.push_back(newHand);
        getline(cin, garbage); // Go to next line
    }

    sort(hands.begin(), hands.end());

    int total = 0;
    for (int i = 0; i < hands.size(); i++) {
        total += (i + 1) * hands[i].getBid();
    }

    cout << total << endl;
}