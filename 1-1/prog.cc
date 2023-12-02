#include <iostream>
#include <string>

using namespace std;

int firstNumberInString(string s);
int lastNumberInString(string s);

int main() {
    string line;
    int total = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        total += (firstNumberInString(line) * 10);
        total += lastNumberInString(line);
    }

    cout << total << endl;
}

int firstNumberInString(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            return s[i] - '0';
        }
    }
    return -1;
}

int lastNumberInString(string s) {
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] >= '0' && s[i] <= '9') {
            return s[i] - '0';
        }
    }
    return -1;
}