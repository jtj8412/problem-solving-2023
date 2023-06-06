#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

struct Data {
    int val, idx; // numbers 원소 값, numbers 내에서 위치한 인덱스.
    Data() : val(-1), idx(-1) {}
    Data(int _val, int _idx) : val(_val), idx(_idx) {}

    // priority_queue 내 오름차순 정렬.
    bool operator<(const Data& data) const {
        return this->val > data.val;
    }
};

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    priority_queue<Data> pq;

    answer.assign(numbers.size(), -1);

    // numbers 앞 부터 순차적으로 진행.
    for (int i = 0; i < numbers.size(); ++i) {
        int num = numbers[i];

        // 현재 탐색 중인 정수보다 작은, 앞의 수들에 대해 정산.
        while (!pq.empty() && pq.top().val < num) {
            answer[pq.top().idx] = num;
            pq.pop();
        }

        pq.push(Data(num, i));
    }

    return answer;
}

int main() {
    vector<int> numbers = { 9, 1, 5, 3, 6, 2 };
    vector<int> answer = solution(numbers);

    cout << "===== answer =====" << endl;
    for (auto ans : answer) {
        cout << ans << endl;
    }
    return 0;
}