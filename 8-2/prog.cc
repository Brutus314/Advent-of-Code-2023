#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

struct Node {
    string left;
    string right;
};

int main() {
    string instructions;
    cin >> instructions;

    unordered_map<string, Node> map;
    vector<string> travellingNodes;
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
        if (nodeName[2] == 'A') {
            travellingNodes.push_back(nodeName);
        }
    }
    
    vector<long long> moves(travellingNodes.size(), 0);

    int instructionsIndex = 0;
    for(int i = 0; i < travellingNodes.size(); i++) {
        instructionsIndex = 0;
        while (travellingNodes[i][2] != 'Z') {
            if (instructions[instructionsIndex] == 'L') {
                travellingNodes[i] = map[travellingNodes[i]].left;
            } else {
                travellingNodes[i] = map[travellingNodes[i]].right;
            }

            moves[i]++;
            instructionsIndex++;
            if (instructionsIndex == instructions.length()) {
                instructionsIndex = 0;
            }
        }
    }

    long long lcmResult = lcm(moves[0], moves[1]);
    for (int i = 2; i < moves.size(); i++) {
        lcmResult = lcm(lcmResult, moves[i]);
    }

    cout << lcmResult << endl;
}