#include "hand.hpp"

using namespace std;

const int HIGH_CARD = 0;
const int PAIR = 1;
const int TWO_PAIR = 2;
const int THREE_OF_A_KIND = 3;
const int FULL_HOUSE = 4;
const int FOUR_OF_A_KIND = 5;
const int FIVE_OF_A_KIND = 6;

unordered_map<char, int> Hand::cardRankMap ({
    {'J', 0},
    {'2', 1},
    {'3', 2},
    {'4', 3},
    {'5', 4},
    {'6', 5},
    {'7', 6},
    {'8', 7},
    {'9', 8},
    {'T', 9},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
});

Hand::Hand() {
    cards = "";
    cardCounts = vector<int>(13, 0);
}

void Hand::setBid(int newBid) {
    bid = newBid;
}

int Hand::getBid() {
    return bid;
}

void Hand::addCard(char c) {
    cards += c;
    cardCounts[cardRankMap[c]]++;
}

int Hand::getHandRank() {
    int handRank = HIGH_CARD;
    for (int i = 1; i < cardCounts.size(); i++) {
        switch (cardCounts[i]) {
            case 0:
            case 1:
                break;
            case 2:
                if (handRank == PAIR) {
                    handRank = TWO_PAIR;
                } else if (handRank == THREE_OF_A_KIND) {
                    handRank = FULL_HOUSE;
                } else {
                    handRank = PAIR;
                }
                break;
            case 3:
                if (handRank == PAIR) {
                    handRank = FULL_HOUSE;
                } else {
                    handRank = THREE_OF_A_KIND;
                }
                break;
            case 4:
                handRank = FOUR_OF_A_KIND;
                break;
            case 5:
                handRank = FIVE_OF_A_KIND;
                break;
            default:
                break;
        }
    }

    // Check how many jokers we have
    switch (cardCounts[0]) {
        case 0:
            break;
        case 1:
            if (handRank == FOUR_OF_A_KIND) {
                handRank = FIVE_OF_A_KIND;
            } else if (handRank == THREE_OF_A_KIND) {
                handRank = FOUR_OF_A_KIND;
            } else if (handRank == TWO_PAIR) {
                handRank = FULL_HOUSE;
            } else if (handRank == PAIR) {
                handRank = THREE_OF_A_KIND;
            } else {
                handRank = PAIR;
            }
            break;
        case 2:
            if (handRank == THREE_OF_A_KIND) {
                handRank = FIVE_OF_A_KIND;
            } else if (handRank == PAIR) {
                handRank = FOUR_OF_A_KIND;
            } else {
                handRank = THREE_OF_A_KIND;
            }
            break;
        case 3:
            if (handRank == PAIR) {
                handRank = FIVE_OF_A_KIND;
            } else {
                handRank = FOUR_OF_A_KIND;
            }
            break;
        case 4:
        case 5:
            handRank = FIVE_OF_A_KIND;
            break;
    }

    return handRank;
}

bool Hand::operator<(Hand other) {
    int myHandRank = getHandRank();
    int otherHandRank = other.getHandRank();

    if (myHandRank != otherHandRank) {
        return myHandRank < otherHandRank;
    }

    for (int i = 0; i < cards.length(); i++) {
        if (cards[i] != other.cards[i]) {
            return cardRankMap[cards[i]] < cardRankMap[other.cards[i]];
        }
    }

    return false;
}