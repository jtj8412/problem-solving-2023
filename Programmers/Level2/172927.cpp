#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <unordered_map>

#define INT_MAX 2147483647

using namespace std;

// key: pickIdx + mineral[0], val: work
unordered_map<int, int> workTable = {
    {100, 1},
    {101, 5},
    {102, 25},

    {105, 1},
    {106, 1},
    {107, 5},

    {115, 1},
    {116, 1},
    {117, 1}
};

// startIdx 번째 광물부터 pick 곡괭이를 사용했을 때 발생하는 피로도 계산.
int calcWork(int pick, const vector<string>& minerals, int startIdx) {
    int work = 0;
    int length = min((int)minerals.size(), startIdx + 5);
    for (int i = startIdx; i < length; ++i) {
        int key = pick + minerals[i][0];
        work += workTable[key];
    }
    return work;
}

int logic(vector<int>& picks, const vector<string>& minerals, int idx = 0, int sum = 0) {
    int remPickCnt = picks[0] + picks[1] + picks[2];

    if (!remPickCnt || idx >= minerals.size()) {
        return sum;
    }

    int result = INT_MAX;

    // 현재 광물 위치에서 각 곡괭이를 사용했을 때의 모든 경우를 확인.
    for (int pickIdx = 0; pickIdx < 3; ++pickIdx) {
        if (!picks[pickIdx]) {
            continue;
        }

        int work = calcWork(pickIdx, minerals, idx);

        // 백트래킹 방식에 따라, 현재 선택된 곡괭이(pickIdx) 갯수를 줄였다가 후에 다시 증가.
        picks[pickIdx]--;
        result = min(result, logic(picks, minerals, idx + 5, sum + work));
        picks[pickIdx]++;
    }

    return result;
}

int solution(vector<int> picks, vector<string> minerals) {
    return logic(picks, minerals); // 재귀
}

int main() {
    vector<int> picks = { 0, 1, 1 };
    vector<string> minerals = { "diamond", "diamond", "diamond", "diamond", "diamond", "iron", "iron", "iron", "iron", "iron", "diamond" };

    int answer = solution(picks, minerals);

    cout << "answer: " << answer << endl;

    return 0;
}