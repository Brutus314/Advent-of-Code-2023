#ifndef NODE
#define NODE

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

struct node {
    std::vector<std::string> targets;
    std::string name;

    virtual std::pair<bool, std::vector<std::string>> sendSignal(bool high, std::string sender) = 0;
};

struct broadcaster : public node {
    std::pair<bool, std::vector<std::string>> sendSignal(bool high, std::string sender) {
        return std::make_pair(high, targets);
    }
};

struct flipFlop : public node {
    bool state;

    flipFlop() {
        state = false;
    }

    std::pair<bool, std::vector<std::string>> sendSignal(bool high, std::string sender) {
        if (!high) {
            state = !state;
            return std::make_pair(state, targets);
        } else {
            return std::make_pair(high, std::vector<std::string>());
        }
    }
};

struct con : public node {
    std::unordered_map<std::string, bool> state;

    std::pair<bool, std::vector<std::string>> sendSignal(bool high, std::string sender) {
        state[sender] = high;

        for (const auto& n : state) {
            if (!n.second) {
                 return std::make_pair(true, targets);
            }
        } 
        return std::make_pair(false, targets);
    }
};

#endif