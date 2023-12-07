#include <string>
#include <vector>
#include <unordered_map>

#ifndef HAND
#define HAND

class Hand {
    private:
    std::string cards;
    std::vector<int> cardCounts;
    int bid;

    public:
    static std::unordered_map<char, int> cardRankMap;
    Hand();
    void setBid(int newBid);
    int getBid();
    void addCard(char c);
    int getHandRank();
    bool operator<(Hand other);
};

#endif