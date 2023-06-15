// 디펜스 게임

#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int solution(int n, int k, vector<int> enemy) {
    int answer = 0, remain = n;
    priority_queue<int> pq; // 현재까지 처치한 적을 내림차순 정렬

    for (int i = 0; i < enemy.size(); ++i) {
        pq.push(enemy[i]);

        // 남는 병사가 없을 경우, 지금까지 처치한 적들 중 많은 수를 대상으로 무적권을 사용
        while (remain - enemy[i] < 0 && !pq.empty() && k > 0) {
            remain += pq.top(); 
            pq.pop();
            k--;
        }

        // 위에서 무적권을 시도했음에도 남는 병사가 없을 경우 디펜스 종료
        if ((remain -= enemy[i]) < 0) {
            break;
        }

        answer++;
    }

    return answer;
}