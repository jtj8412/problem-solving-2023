#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

const unordered_map<char, pair<int, int>> DIRECTION = {
    {'E', {1, 0}},
    {'S', {0, 1}},
    {'W', {-1, 0}},
    {'N', {0, -1}},
};

vector<int> solution(vector<string> park, vector<string> routes) {
    pair<int, int> pos = { -1, -1 };
    int w = park[0].size(), h = park.size();

    // init start position.
    for (int i = 0; i < h; ++i) {
        bool bOk = false;

        for (int j = 0; j < w; ++j) {
            if (park[i][j] == 'S') {
                pos = { j, i };
                bOk = true;
                break;
            }
        }

        if (bOk) {
            break;
        }
    }
    
    // process.
    for (int i = 0; i < routes.size(); ++i) {
        const pair<int, int>& move = DIRECTION.find(routes[i][0])->second;
        int step = routes[i][2] - '0';

        // validate.
        bool bOk = true;
        for (int j = 0; j < step; ++j) {
            pair<int, int> next = {
                pos.first + move.first * (j + 1),
                pos.second + move.second * (j + 1)
            };

            if (next.first < 0 || next.second < 0 || next.first >= w || next.second >= h || park[next.second][next.first] == 'X') {
                bOk = false;
                break;
            }
        }

        // move.
        if (bOk) {
            pos.first += move.first * step;
            pos.second += move.second * step;
        }
    }

    return { pos.second, pos.first };
}