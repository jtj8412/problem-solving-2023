#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    unordered_map<string, int> order;

    // init
    for (int i = 0; i < players.size(); ++i) {
        answer.push_back(players[i]);
        order[players[i]] = i;
    }

    // logic
    for (int i = 0; i < callings.size(); ++i) {
        int n = order[callings[i]];
        order[callings[i]]--;
        order[answer[n - 1]]++;
        swap(answer[n - 1], answer[n]);
    }

    return answer;
}