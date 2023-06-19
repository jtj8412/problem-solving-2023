#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int n, int m, vector<int> section) {
    int answer = 0;
    int cur = -0xfffffff;

    for (int i = 0; i < section.size(); ++i) {
        if (cur + (m - 1) < section[i]) {
            cur = section[i];
            answer++;
        }
    }

    return answer;
}