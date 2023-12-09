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

        sequences[index].insert(sequences[index].begin(), 0);
        for (int i = index - 1; i >= 0; i--) {
            sequences[i].insert(sequences[i].begin(), sequences[i][0] - sequences[i + 1][0]);
        }

        total += sequences[0][0];
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