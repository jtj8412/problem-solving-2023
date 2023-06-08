#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

long long logic(int cap, int n, const vector<int>& vec) {
    long long ret = 0;
    int remain = 0, right = n;

    for (int i = n - 1; i >= 0; --i) {
        int cnt = vec[i];
        int amt = min(cnt, cap - remain);

        if (remain == 0) right = i;

        remain += amt;
        cnt -= amt;

        if (remain < cap) continue;
        
        ret += (right + 1) * 2;
        ret += (cnt / cap) * (i + 1) * 2;
        remain = cnt % cap;
        
        if (remain > 0) right = i;
    }

    if (remain > 0) {
        ret += (right + 1) * 2;
    }

    return ret;
}

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    return max(logic(cap, n, deliveries), logic(cap, n, pickups));
}

int main() {
    int cap = 4;
    int n = 5;
    vector<int> deliveries = {1,0,3,1,2};
    vector<int> pickups = {0,3,0,4,0};

    cout << "answer: " << solution(cap, n, deliveries, pickups);
}