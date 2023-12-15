#include <iostream>
#include <string>

using namespace std;

int main() {
    int total = 0;
    int current = 0;
    string line;
    getline(cin, line);

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            total += current;
            current = 0;
        } else {
            current += line[i];
            current *= 17;
            current %= 256;
        }
    }

    total += current;

    cout << total << endl;;
}