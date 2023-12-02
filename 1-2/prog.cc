#include <iostream>
#include <string>

using namespace std;

int firstNumberInString(string s);
int lastNumberInString(string s);
int firstNumberWordInString(string s);
int lastNumberWordInString(string s);

int main() {
    string line;
    int total = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        int result = (firstNumberInString(line) * 10) + lastNumberInString(line);

        total += result;
    }

    cout << total << endl;
}

int firstNumberInString(string s) {
    int index = -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            index = i;
            break;
        }
    }
    string trimmedString;
    
    if (index == -1) {
        trimmedString = s;
    } else {
        trimmedString = s.substr(0, index);
    }

    int numberWordFound = firstNumberWordInString(trimmedString);
    if (numberWordFound != -1) {
        return numberWordFound;
    }

    return s[index] - '0';
}

int lastNumberInString(string s) {
    int index = -1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] >= '0' && s[i] <= '9') {
            index = i;
            break;
        }
    }

    string trimmedString;
    
    if (index == -1) {
        trimmedString = s;
    } else {
        trimmedString = s.substr(index + 1);
    }

    int numberWordFound = lastNumberWordInString(trimmedString);
    if (numberWordFound != -1) {
        return numberWordFound;
    }

    return s[index] - '0';
}

int firstNumberWordInString(string s) {
    int index = -1;
    int currentNumberFound = -1;

    int findIndex = s.find("one");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 1;
    }
    findIndex = s.find("two");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 2;
    }
    findIndex = s.find("three");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 3;
    }
    findIndex = s.find("four");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 4;
    }
    findIndex = s.find("five");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 5;
    }
    findIndex = s.find("six");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 6;
    }
    findIndex = s.find("seven");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 7;
    }
    findIndex = s.find("eight");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 8;
    }
    findIndex = s.find("nine");
    if (findIndex != -1 && (findIndex < index || index == -1)) {
        index = findIndex;
        currentNumberFound = 9;
    }

    return currentNumberFound;
}

int lastNumberWordInString(string s) {
    int index = -1;
    int currentNumberFound = -1;

    int findIndex = s.rfind("one");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 1;
    }
    findIndex = s.rfind("two");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 2;
    }
    findIndex = s.rfind("three");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 3;
    }
    findIndex = s.rfind("four");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 4;
    }
    findIndex = s.rfind("five");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 5;
    }
    findIndex = s.rfind("six");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 6;
    }
    findIndex = s.rfind("seven");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 7;
    }
    findIndex = s.rfind("eight");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 8;
    }
    findIndex = s.rfind("nine");
    if (findIndex > index) {
        index = findIndex;
        currentNumberFound = 9;
    }

    return currentNumberFound;
}