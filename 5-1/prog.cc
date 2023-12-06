#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct conversion {
    long long destinationRangeStart;
    long long sourceRangeStart;
    long long range;
};

vector<long long> splitNumbers(string s);
vector<conversion> readConversionFromCin();
long long convertValue(vector<conversion>& conversions, long long sourceValue);

int main() {
    string garbage;
    cin >> garbage; // Seeds:
    
    string rest;
    getline(cin, rest);

    vector<long long> seeds = splitNumbers(rest);

    getline(cin, garbage); // Empty
    getline(cin, garbage); // Seed-To-Soil Map

    vector<vector<conversion>> conversions(7);

    for (int i = 0; i < 7; i++) {
        conversions[i] = readConversionFromCin();
        getline(cin, garbage); // Header
    }

    long long closestLocation = INT64_MAX;

    for (int i = 0; i < seeds.size(); i++) {
        long long value = seeds[i];
        for (int j = 0; j < 7; j++) {
            value = convertValue(conversions[j], value);
        }

        if (value < closestLocation) {
            closestLocation = value;
        }
    }

    cout << closestLocation << endl;
}

vector<long long> splitNumbers(string s) {
    vector<long long> i;
    long long num;
    stringstream ss;

    ss << s;
    while (ss >> num) {
        i.push_back(num);
    }

    return i;
}

// Assume pointer is at first numerical line
vector<conversion> readConversionFromCin() {
    vector<conversion> conversions;
    string numbers;

    while (getline(cin, numbers) && !numbers.empty()) {
        vector<long long> results = splitNumbers(numbers);
        conversion newConversion;
        newConversion.destinationRangeStart = results[0];
        newConversion.sourceRangeStart = results[1];
        newConversion.range = results[2];
        conversions.push_back(newConversion);
    }

    return conversions;
}

long long convertValue(vector<conversion>& conversions, long long sourceValue) {
    for (int i = 0; i < conversions.size(); i++) {
        if (sourceValue >= conversions[i].sourceRangeStart && sourceValue < conversions[i].sourceRangeStart + conversions[i].range) {
            return sourceValue + (conversions[i].destinationRangeStart - conversions[i].sourceRangeStart);
        }
    }

    return sourceValue;
}