#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> keymap, vector<string> targets) {
    vector<int> answer;
    unordered_map<char, int> um;

    // init map
    for (int i = 0; i < keymap.size(); ++i) {
        const string& key = keymap[i];
        for (int j = 0; j < key.size(); ++j) {
            auto iter = um.find(key[j]);
            if (iter == um.end() || iter->second > j + 1) {
                um[key[j]] = j + 1;
            }
        }
    }
    
    for (int i = 0; i < targets.size(); ++i) {
        const string& target = targets[i];
        int cnt = 0;
        for (int j = 0; j < target.size(); ++j) {
            auto iter = um.find(target[j]);
            if (iter == um.end()) {
                cnt = -1;
                break;
            }
            cnt += iter->second;
            
        }
        answer.push_back(cnt);
    }

    return answer;
}