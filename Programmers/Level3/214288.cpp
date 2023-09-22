#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

void dump(const vector<int>& teachers, int wait) {
    cout << "===== dump =====" << endl;
    cout << "wait: " << wait << endl;
    cout << teachers[0];
    for (int i = 1; i < teachers.size(); ++i) {
        cout << ", " << teachers[i];
    }
    cout << endl;
}

// 로직 수행
int logic(vector<int>& teachers, const vector<vector<int>>& reqs) {
    int wait = 0;
    vector<priority_queue<int, vector<int>, greater<int>>> lasts(teachers.size());

    for (int i = 0; i < reqs.size(); ++i) {
        int startTime = reqs[i][0];
        int teachTime = reqs[i][1];
        int type = reqs[i][2] - 1;

        auto& last = lasts[type];

        if (last.size() == teachers[type]) {
            int lastEndTime = last.top();
            last.pop();

            if (lastEndTime > startTime) {
                wait += lastEndTime - startTime;
                startTime = lastEndTime;
            }
        }

        last.push(startTime + teachTime);
    }

    // dump(teachers, wait);

    return wait;
}

// 재귀돌면서 teachers 를 초기화 및 로직 수행
int recursive(
    int idx,
    int remain,
    vector<int>& teachers, 
    const vector<vector<int>>& reqs) 
{
    // teachers 초기화 완료 시 로직 수행
    if (idx == teachers.size()) {
        return logic(teachers, reqs);
    }

    int resultMin = 0x7fffffff;

    // teachers[idx] 초기화
    for (int i = 0; i <= remain; ++i) {
        teachers[idx] = i + 1;

        // teachers[idx + 1] 초기화
        int result = recursive(idx + 1, remain - i, teachers, reqs);

        // logic 결과 중 최솟값 저장
        if (result < resultMin) {
            resultMin = result;
        }
    }

    return resultMin;
}

int solution(int k, int n, vector<vector<int>> reqs) {
    vector<int> teachers(k);

    int answer = recursive(0, n - k, teachers, reqs);

    return answer;
}