#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

string solution(string s, string skip, int index) {
    string answer = "";
    vector<char> alphas;
    set<char> skips;
    map<char, int> alphaIdxes;

    // init usable alphas.
    for (int i = 0; i < skip.size(); ++i) {
        skips.insert(skip[i]);
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (skips.find(ch) == skips.end()) {
            alphas.push_back(ch);
            alphaIdxes[ch] = alphas.size() - 1;
        }
    }

    int size = alphas.size();

    // logic.
    for (int i = 0; i < s.size(); ++i) {
        int idx = (alphaIdxes[(s[i])] + index) % size;
        answer.push_back(alphas[idx]);
    }

    return answer;
}
