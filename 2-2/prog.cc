#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    string garbage;
    int total = 0;
    int id;

    int numberOfCubesRevealed;
    string colorOfCubesRevealed;

    while (cin >> garbage) { // Game
        bool endOfLine = false;
        int minRedUsed = 0, minGreenUsed = 0, minBlueUsed = 0;
        cin >> id;
        cin >> garbage; // :

        while (!endOfLine) {
            cin >> numberOfCubesRevealed >> colorOfCubesRevealed;

            // Account for ending comma or colon
            if (colorOfCubesRevealed.find_first_of(",;") == string::npos) {
                endOfLine = true;
            } else {
                colorOfCubesRevealed = colorOfCubesRevealed.substr(0, colorOfCubesRevealed.length() - 1);
            }

            if (colorOfCubesRevealed == "red") {
                minRedUsed = max(minRedUsed, numberOfCubesRevealed);
            } else if (colorOfCubesRevealed == "green") {
                minGreenUsed = max(minGreenUsed, numberOfCubesRevealed);
            } else if (colorOfCubesRevealed == "blue") {
                minBlueUsed = max(minBlueUsed, numberOfCubesRevealed);
            }

            if (endOfLine) {
                total += (minRedUsed * minGreenUsed * minBlueUsed);
            }
        }
    }

    cout << total << endl;
}