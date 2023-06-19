#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> name, vector<int> yearning, vector<vector<string>> photo) {
    vector<int> answer;
    unordered_map<string, int> yearningTable;

    answer.assign(photo.size(), 0);

    // init yearningTable
    for (int i = 0; i < name.size(); ++i) {
        yearningTable.insert(make_pair(name[i], yearning[i]));
    }

    // logic
    for (int i = 0; i < photo.size(); ++i) {
        for (int j = 0; j < photo[i].size(); ++j) {
            answer[i] += yearningTable[photo[i][j]];
        }
    }

    return answer;
}