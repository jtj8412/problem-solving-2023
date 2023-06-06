#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

// 조건에 충족 시 해당 값을 대기열에 추가.
void tryEnqueue(int num, int prevNum, int y, vector<int>& visited, queue<int>& q) {
    // 1. y 보다 큰 값이 나올 경우 앞으로 y 에 도달할 수 없음.
    // 2. 이미 탐색했던 값일 경우 재탐색은 의미 없음.
    if (num > y || visited[num]) 
        return;

    q.push(num); // 대기열 추가.
    visited[num] = visited[prevNum] + 1; // 방문 체크.
}

int solution(int x, int y, int n) {
    int answer = -1;
    queue<int> q;
    vector<int> visited;

    visited.assign((size_t)(y + 1), 0);

    q.push(x);

    while (!q.empty()) {
        int num = q.front(); q.pop();

        if (num == y) {
            answer = visited[num];
            break;
        }

        // 세 연산 모두 시도, y에 도달할 수 있는 가능성이 있는 값일 경우 대기열에 추가.
        tryEnqueue(num + n, num, y, visited, q);
        tryEnqueue(num * 2, num, y, visited, q);
        tryEnqueue(num * 3, num, y, visited, q);
    }

    return answer;
}

int main() {
    int x = 10, y = 40, n = 5;
    int answer = solution(x, y, n);

    cout << "answer: " << answer << endl;
}