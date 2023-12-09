#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> splitNumbers(string s);
bool allZeroes(vector<int>& nums);
vector<int> sequenceDifference(vector<int>& nums);

int main() {
    string numberString;
    int total = 0;
    while (getline(cin, numberString)) {
        vector<vector<int>> sequences;
        vector<int> numbers = splitNumbers(numberString);
        sequences.push_back(numbers);
        int index = 0;
        
        while (!allZeroes(sequences[index])) {
            sequences.push_back(sequenceDifference(sequences[index]));
            index++;
        }

        sequences[index].push_back(0);
        for (int i = index - 1; i >= 0; i--) {
            sequences[i].push_back(sequences[i].back() + sequences[i + 1].back());
        }

        total += sequences[0].back();
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

bool allZeroes(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            return false;
        }
    }
    return true;
}

vector<int> sequenceDifference(vector<int>& nums) {
    vector<int> newSequence;
    for (int i = 0; i < nums.size() - 1; i++) {
        newSequence.push_back(nums[i + 1] - nums[i]);
    }
    return newSequence;
}