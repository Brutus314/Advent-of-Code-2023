#include <iostream>
#include <string>

using namespace std;

int main() {
    string garbage;
    int total = 0;
    int id;

    int numberOfCubesRevealed;
    string colorOfCubesRevealed;

    while (cin >> garbage) { // Game
        bool endOfLine = false;
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
                if (numberOfCubesRevealed > 12) {
                    getline(cin, garbage);
                    break;
                }
            } else if (colorOfCubesRevealed == "green") {
                if (numberOfCubesRevealed > 13) {
                    getline(cin, garbage);
                    break;
                }
            } else if (colorOfCubesRevealed == "blue") {
                if (numberOfCubesRevealed > 14) {
                    getline(cin, garbage);
                    break;
                }
            }

            if (endOfLine) {
                total += id;
            }
        }
    }

    cout << total << endl;
}