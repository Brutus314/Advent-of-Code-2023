#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const double MIN_BOUND = 200000000000000;
const double MAX_BOUND = 400000000000000;

struct vectorLine {
    double startX;
    double startY;
    double startZ;

    double vX;
    double vY;
    double vZ;

    double slope() {
        return vY / vX;
    }

    double yIntercept() {
        return startY - (slope() * startX);
    }
};

pair<double, double> intersect(vectorLine l1, vectorLine l2);

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

    int total = 0;

    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {
            if (abs(lines[i].slope() - lines[j].slope()) < .0001) {
                continue;
            } else {
                pair<double, double> intersectionPoint = intersect(lines[i], lines[j]);
                if ((lines[i].vX > 0 && intersectionPoint.first < lines[i].startX) || 
                    (lines[i].vX < 0 && intersectionPoint.first > lines[i].startX) || 
                    (lines[j].vX > 0 && intersectionPoint.first < lines[j].startX) || 
                    (lines[j].vX < 0 && intersectionPoint.first > lines[j].startX)) {
                    continue;
                } else if (intersectionPoint.first > MAX_BOUND || intersectionPoint.second > MAX_BOUND || 
                    intersectionPoint.first < MIN_BOUND || intersectionPoint.second < MIN_BOUND) {
                    continue;
                } else {
                    total++;
                }
            }
        }
    }

    cout << total << endl;
}

// Assumption: lines are not parallel
pair<double, double> intersect(vectorLine l1, vectorLine l2) {
    double iX = (l2.yIntercept() - l1.yIntercept()) / (l1.slope() - l2.slope());
    double iY = (l1.slope() * iX) + l1.yIntercept();
    return make_pair(iX, iY);
}