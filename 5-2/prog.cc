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

struct range {
    long long start;
    long long range;
};

vector<long long> splitNumbers(string s);
vector<conversion> readConversionFromCin();
vector<range> convertRanges(vector<conversion>& conversions, vector<range>& sourceRanges);

int main() {
    string garbage;
    cin >> garbage; // Seeds:
    
    string rest;
    getline(cin, rest);

    vector<long long> seeds = splitNumbers(rest);

    vector<range> seedRanges;
    for (int i = 0; i < seeds.size(); i += 2) {
        range newRange;
        newRange.start = seeds[i];
        newRange.range = seeds[i + 1];
        seedRanges.push_back(newRange);
    }

    getline(cin, garbage); // Empty
    getline(cin, garbage); // Seed-To-Soil Map

    vector<vector<conversion>> conversions(7);

    for (int i = 0; i < 7; i++) {
        conversions[i] = readConversionFromCin();
        getline(cin, garbage); // Header
    }

    for (int i = 0; i < 7; i++) {
        seedRanges = convertRanges(conversions[i], seedRanges);
    }

    long long closestLocation = INT64_MAX;

    for (int i = 0; i < seedRanges.size(); i++) {
        if (seedRanges[i].start < closestLocation) {
            closestLocation = seedRanges[i].start;
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

vector<range> convertRanges(vector<conversion>& conversions, vector<range>& sourceRanges) {
    vector<range> newRanges;
    range curRange;

    while (!sourceRanges.empty()) {
        curRange = sourceRanges.back();
        sourceRanges.pop_back();

        bool found = false;

        for (int i = 0; i < conversions.size(); i++) {
            // Check for overlap
            long long sourceEnd = curRange.start + curRange.range - 1;
            long long conversionEnd = conversions[i].sourceRangeStart + conversions[i].range - 1;

            // Need to find out the type of overlap
            if (curRange.start >= conversions[i].sourceRangeStart && sourceEnd <= conversionEnd) {
                // This range is completely contained. 
                range newRange;
                newRange.range = curRange.range;
                newRange.start = curRange.start + (conversions[i].destinationRangeStart - conversions[i].sourceRangeStart);
                newRanges.push_back(newRange);

                found = true;
                break;
            }
            if (curRange.start >= conversions[i].sourceRangeStart && sourceEnd > conversionEnd && curRange.start <= conversionEnd) {
                // This range is partially contained; It sticks out on the end
                range newRange;
                newRange.range = conversionEnd - curRange.start + 1;
                newRange.start = curRange.start + (conversions[i].destinationRangeStart - conversions[i].sourceRangeStart);
                newRanges.push_back(newRange);

                range leftOvers;
                leftOvers.range = curRange.range - newRange.range;
                leftOvers.start = conversionEnd + 1;
                sourceRanges.push_back(leftOvers);

                found = true;
                break;
            }
            if (curRange.start < conversions[i].sourceRangeStart && sourceEnd <= conversionEnd && sourceEnd >= conversions[i].sourceRangeStart) {
                // This range is partially contained; It sticks out on the beginning
                range newRange;
                newRange.range = sourceEnd - conversions[i].sourceRangeStart + 1;
                newRange.start = conversions[i].sourceRangeStart + (conversions[i].destinationRangeStart - conversions[i].sourceRangeStart);
                newRanges.push_back(newRange);

                range leftOvers;
                leftOvers.range = curRange.range - newRange.range;
                leftOvers.start = curRange.start;
                sourceRanges.push_back(leftOvers);

                found = true;
                break;
            }
            if (curRange.start < conversions[i].sourceRangeStart && sourceEnd > conversionEnd) {
                // This range completely contains the conversion range: we have two extensions
                range newRange;
                newRange.range = conversions[i].range;
                newRange.start = conversions[i].destinationRangeStart;
                newRanges.push_back(newRange);

                range leftOversL;
                leftOversL.range = conversions[i].sourceRangeStart - curRange.start + 1;
                leftOversL.start = curRange.start;
                sourceRanges.push_back(leftOversL);

                range leftOversR;
                leftOversR.range = curRange.range - (newRange.range + leftOversL.range);
                leftOversR.start = conversionEnd + 1;
                sourceRanges.push_back(leftOversR);

                found = true;
                break;
            }
        }

        if (!found) {
            // Didn't overlap, it's itself
            newRanges.push_back(curRange);
        }
    }
    return newRanges;
}