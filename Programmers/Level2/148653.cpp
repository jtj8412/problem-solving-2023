// 마법의 엘리베이터

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// @cnt 는 무한재귀를 멈추기 위해 넣은 값
int dfs(int storey, int ans = 0, int cnt = 0) {
    // 더 이상 엘리베이터를 움직일 수 없을 때 현재까지 축적된 값(ans) 반환
    if (storey == 0 || cnt > 9) {
        return ans;
    }

    // 현재 자릿수에서 엘리베이터를 위로(+) 이동할건지 아래로(-) 이동할건지 두 경우 모두 계산
    // 즉 경우의 수는 대략 2^9
    int a = dfs(storey / 10, ans + (storey % 10), cnt + 1);
    int b = dfs(storey / 10 + 1, ans + (10 - storey % 10), cnt + 1);

    // 더 최소로 움직인 결과를 반환
    return min(a, b);
}

int solution(int storey) {
    return dfs(storey);
}