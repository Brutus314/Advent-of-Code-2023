#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct bar {
    long long x;
    long long y;
    long long length;
    bool isLower;

    bool operator<(const bar other) {
        if (y == other.y) {
            return x < other.x;
        }
        return y > other.y;
    }
};

bool narrowingIntersectLeft(bar top, bar bottom);
bool narrowingIntersectRight(bar top, bar bottom);
bool wideningIntersectLeft(bar top, bar bottom);
bool wideningIntersectRight(bar top, bar bottom);
bool splitIntersect(bar top, bar bottom);
bool stopIntersect(bar top, bar bottom);

int main() {
    string garbage;
    string color;

    long long x = 0, y = 0;
    deque<bar> bars;

    while (cin >> garbage) {
        cin >> garbage;
        cin >> color;
        color = color.substr(2, color.length() - 3);
        long long distance = stoull(color.substr(0, 5), nullptr, 16);
        bar newBar;

        switch (color[5]) {
            case '3':
                y += distance;
                break;
            case '1':
                y -= distance;
                break;
            case '2':
                x -= distance;
                newBar.x = x;
                newBar.y = y;
                newBar.length = distance + 1;
                newBar.isLower = false;
                bars.push_back(newBar);
                break;
            case '0':
                newBar.x = x;
                newBar.y = y;
                newBar.length = distance + 1;
                newBar.isLower = false;
                x += distance;
                bars.push_back(newBar);
                break;
        }
    }

    sort(bars.begin(), bars.end());

    long long total = 0;

    while (!bars.empty()) {
        bar toCheck = bars.front();
        bars.pop_front();

        if (toCheck.isLower) {
            continue;
        }

        for (int i = 0; i < bars.size(); i++) {
            if (bars[i].isLower) {
                continue;
            }
            if (stopIntersect(toCheck, bars[i])) {
                total += (toCheck.y - bars[i].y + 1) * toCheck.length;
                bars[i].isLower = true;
                break;
            } else if (narrowingIntersectLeft(toCheck, bars[i])) {
                bar newBar;
                newBar.x = (bars[i].x + bars[i].length - 1);
                newBar.y = bars[i].y;
                newBar.length = (toCheck.length - bars[i].length) + 1;
                newBar.isLower = false;
                total += ((toCheck.y - bars[i].y + 1) * toCheck.length) - newBar.length;
                bars[i].isLower = true;
                bars.push_back(newBar);
                sort(bars.begin(), bars.end());
                break;
            } else if (narrowingIntersectRight(toCheck, bars[i])) {
                bar newBar;
                newBar.x = toCheck.x;
                newBar.y = bars[i].y;
                newBar.length = (toCheck.length - bars[i].length) + 1;
                newBar.isLower = false;
                total += ((toCheck.y - bars[i].y + 1) * toCheck.length) - newBar.length;
                bars[i].isLower = true;
                bars.push_back(newBar);
                sort(bars.begin(), bars.end());
                break;
            } else if (wideningIntersectLeft(toCheck, bars[i])) {
                total += (toCheck.y - bars[i].y) * toCheck.length;
                bars[i].length += toCheck.length;
                bars[i].length --;
                break;
            } else if (wideningIntersectRight(toCheck, bars[i])) {
                total += (toCheck.y - bars[i].y) * toCheck.length;
                bars[i].x = toCheck.x;
                bars[i].length += toCheck.length;
                bars[i].length --;
                sort(bars.begin(), bars.end());
                break;
            } else if (splitIntersect(toCheck, bars[i])) {
                bar newLeft, newRight;
                bars[i].isLower = true;

                newLeft.x = toCheck.x;
                newLeft.y = bars[i].y;
                newLeft.length = (bars[i].x - toCheck.x + 1);
                newLeft.isLower = false;

                newRight.x = (bars[i].x + bars[i].length - 1);
                newRight.y = bars[i].y;
                newRight.length = (toCheck.length - newLeft.length - bars[i].length) + 2;
                newRight.isLower = false;
                total += ((toCheck.y - bars[i].y + 1) * toCheck.length) - newLeft.length - newRight.length;

                bars.push_back(newLeft);
                bars.push_back(newRight);
                sort(bars.begin(), bars.end());
                break;
            }
        }
    }

    cout << total << endl;
}

// Narrowing intersection IF:
    // Top bar start = bottom bar start OR
    // Top bar end = bottom bar end

// Widening intersection IF:
    // Top bar start = bottom bar end OR
    // Top bar end = bottom bar start

// Split intersection IF:
    // Top bar start < bottom bar start AND
    // Top bar end > bottom bar end

// Complete stop intersection IF:
    // Top bar start >= bottom bar start AND
    // Top bar end <= bottom bar end

bool narrowingIntersectLeft(bar top, bar bottom) {
    return top.x == bottom.x;
}

bool narrowingIntersectRight(bar top, bar bottom) {
    return (top.x + top.length - 1) == (bottom.x + bottom.length - 1);
}

bool wideningIntersectLeft(bar top, bar bottom) {
    return top.x == (bottom.x + bottom.length - 1);
}

bool wideningIntersectRight(bar top, bar bottom) {
    return (top.x + top.length - 1) == bottom.x;
}

bool splitIntersect(bar top, bar bottom) {
    return (top.x < bottom.x) && ((top.x + top.length - 1) > (bottom.x + bottom.length - 1));
}

bool stopIntersect(bar top, bar bottom) {
    return (top.x >= bottom.x) && ((top.x + top.length - 1) <= (bottom.x + bottom.length - 1));
}