#include <string>
#include <vector>
#include <iostream>

using namespace std;

const string YES = "Yes";
const string NO = "No";

bool logic(int idx1, int idx2, int goalIdx, const vector<string>& cards1, const vector<string>& cards2, const vector<string>& goal) {
    if (goalIdx == goal.size()) {
        return true;
    }

    if (idx1 < cards1.size() && cards1[idx1] == goal[goalIdx]) {
        if (logic(idx1 + 1, idx2, goalIdx + 1, cards1, cards2, goal)) {
            return true;
        }
    }

    if (idx2 < cards2.size() && cards2[idx2] == goal[goalIdx]) {
        if (logic(idx1, idx2 + 1, goalIdx + 1, cards1, cards2, goal)) {
            return true;
        }
    }

    return false;
}

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    bool ret = logic(0, 0, 0, cards1, cards2, goal);
    return ret ? YES : NO;
}