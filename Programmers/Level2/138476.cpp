// 귤 고르기

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}

int solution(int k, vector<int> tangerine) {
    int answer = 0, remain = k;
    unordered_map<int, int> um;

    // 귤의 무게별 갯수
    for (int i = 0; i < tangerine.size(); ++i) {
        um[tangerine[i]]++;
    }

    // 무게별 갯수가 많은 순으로 정렬
    vector<pair<int, int>> vec(um.begin(), um.end());
    sort(vec.begin(), vec.end(), compare);

    // 계산
    for (int i = 0; i < vec.size(); ++i) {
        answer++;
        if ((remain -= vec[i].second) <= 0) {
            break;
        }
    }

    return answer;
}