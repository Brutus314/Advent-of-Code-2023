#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Node {
    string left;
    string right;
};

int main() {
    string instructions;
    cin >> instructions;

    unordered_map<string, Node> map;
    string nodeName;
    string leftNode;
    string rightNode;
    string garbage;
    while (cin >> nodeName) {
        Node newNode;
        cin >> garbage; // =
        cin >> leftNode >> rightNode;

        newNode.left = leftNode.substr(1, 3); // Remove paranthesis and comma
        newNode.right = rightNode.substr(0, 3); // Remove paranthesis
        map[nodeName] = newNode;
    }

    string currentNodeName = "AAA";
    Node currentNode;
    int moves = 0;
    int instructionsIndex = 0;
    while (currentNodeName != "ZZZ") {
        currentNode = map[currentNodeName];
        if (instructions[instructionsIndex] == 'L') {
            currentNodeName = currentNode.left;
        } else {
            currentNodeName = currentNode.right;
        }

        moves++;
        instructionsIndex++;
        if (instructionsIndex == instructions.length()) {
            instructionsIndex = 0;
        }
    }

    cout << moves << endl;
}