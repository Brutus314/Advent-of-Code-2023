// Big disclaimer: this is not my original solution. I spent a lot of time on the reddit looking for an explanation that I could follow
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

const double MIN_BOUND = 200000000000000;
const double MAX_BOUND = 400000000000000;

struct vectorLine {
    long long startX;
    long long startY;
    long long startZ;

    long long vX;
    long long vY;
    long long vZ;

    vectorLine() {}

    vectorLine(const vectorLine& other) {
        startX = other.startX;
        startY = other.startY;
        startZ = other.startZ;
        vX = other.vX;
        vY = other.vY;
        vZ = other.vZ;
    }

    double slope() {
        return static_cast<double>(vY) / vX;
    }

    double yIntercept() {
        return startY - (slope() * startX);
    }
};

pair<long long, long long> intersect(vectorLine& l1, vectorLine& l2);
vector<int> setIntersection(vector<int>& v1, vector<int>& v2);

int main() {
    double num;
    vector<vectorLine> lines;
    while (cin >> num) {
        vectorLine newLine;
        newLine.startX = num;
        cin.ignore();
        cin >> newLine.startY;
        cin.ignore();
        cin >> newLine.startZ;
        cin.ignore(2);

        cin >> newLine.vX;
        cin.ignore();
        cin >> newLine.vY;
        cin.ignore();
        cin >> newLine.vZ;

        lines.push_back(newLine);
    }

    vector<int> potentialX;
    vector<int> potentialY;
    vector<int> potentialZ;
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines.size(); j++) {
            vector<int> thisX;
            vector<int> thisY;
            vector<int> thisZ;

            if (i == j) continue;

            if (lines[i].vX == lines[j].vX) {
                for (int x = -1000; x <= 1000; x++) {
                    if (x == lines[i].vX) thisX.push_back(x);
                    else if ((lines[i].startX - lines[j].startX) % (x - lines[i].vX) == 0) thisX.push_back(x);
                }
                if (potentialX.size() == 0) {
                    potentialX = thisX;
                } else {
                    potentialX = setIntersection(potentialX, thisX);
                }
            }
            if (lines[i].vY == lines[j].vY) {
                for (int y = -1000; y <= 1000; y++) {
                    if (y == lines[i].vY) thisY.push_back(y);
                    else if ((lines[i].startY - lines[j].startY) % (y - lines[i].vY) == 0) thisY.push_back(y);
                }
                if (potentialY.size() == 0) {
                    potentialY = thisY;
                } else {
                    potentialY = setIntersection(potentialY, thisY);
                }
            }
            if (lines[i].vZ == lines[j].vZ) {
                for (int z = -1000; z <= 1000; z++) {
                    if (z == lines[i].vZ) thisZ.push_back(z);
                    else if ((lines[i].startZ - lines[j].startZ) % (z - lines[i].vZ) == 0) thisZ.push_back(z);
                }
                if (potentialZ.size() == 0) {
                    potentialZ = thisZ;
                } else {
                    potentialZ = setIntersection(potentialZ, thisZ);
                }
            }
        }
    }

    int rVX = potentialX[0];
    int rVY = potentialY[0];
    int rVZ = potentialZ[0];

    vectorLine adjustedLineA(lines[0]);
    adjustedLineA.vX -= rVX;
    adjustedLineA.vY -= rVY;
    adjustedLineA.vZ -= rVZ;

    vectorLine adjustedLineB(lines[1]);
    adjustedLineB.vX -= rVX;
    adjustedLineB.vY -= rVY;
    adjustedLineB.vZ -= rVZ;

    pair<long long, long long> rockXAndY = intersect(adjustedLineA, adjustedLineB);

    long long time = (rockXAndY.first - lines[0].startX) / (lines[0].vX - rVX);
    long long z = (adjustedLineA.vZ * time) + adjustedLineA.startZ;

    cout << rockXAndY.first + rockXAndY.second + z << endl;
}

// Assumption: lines are not parallel
pair<long long, long long> intersect(vectorLine& l1, vectorLine& l2) {
    long long iX = round((l2.yIntercept() - l1.yIntercept()) / (l1.slope() - l2.slope()));
    long long iY = round((l1.slope() * iX) + l1.yIntercept());
    return make_pair(iX, iY);
}

vector<int> setIntersection(vector<int>& v1, vector<int>& v2) {
    vector<int> x;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    int i = 0;
    int j = 0;

    while (i < v1.size() && j < v2.size()) {
        if (v1[i] == v2[j]) {
            x.push_back(v1[i]);
            i++;
            j++;
        } else if (v1[i] > v2[j]) {
            j++;
        } else {
            i++;
        }
    }

    return x;
}