#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <string>
#include <stack>

#define INT_MAX 2147483647

using namespace std;

struct Data {
    string* name; // 과제명
    int start; // 시작 시간
    int playtime; // 남은 시간

    Data() 
        : name(nullptr), start(-1), playtime(-1) {}
    Data(const Data& data)
        :name(data.name), start(data.start), playtime(data.playtime) {}
    Data(string* _name, int _start, int _playtime)
        :name(_name), start(_start), playtime(_playtime) {}
};

struct DataComparer {
    bool operator()(Data& a, Data& b) {
        return a.start > b.start;
    }
};

int clock2int(const string& clock) {
    return (clock[0] - '0') * 600
        + (clock[1] - '0') * 60
        + (clock[3] - '0') * 10
        + (clock[4] - '0');
}

void debugLog(int code, const Data& task, int curTime, const vector<string>& answer) {
    //return;
    cout << code << " " << *task.name << 
        " startTime: " << task.start << 
        ", playtime: " << task.playtime << 
        ", curTime: " << curTime << endl;
    cout << "===== answer =====" << endl;
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i] << endl;
    }
    cout << endl;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    priority_queue<Data, vector<Data>, DataComparer> pq;
    stack<Data> delayed;
    Data task;
    int t = 0;

    // init
    for (vector<string>& plan : plans) {
        Data data = Data(&plan[0], clock2int(plan[1]), stoi(plan[2]));
        pq.push(data);
    }
    task = pq.top(); pq.pop();
    t = task.start;
    debugLog(0, task, t, answer);

    while (true) {
        int curPlanEndTime = t + task.playtime;
        int nextPlanStartTime = INT_MAX;
        if (!pq.empty()) {
            nextPlanStartTime = pq.top().start;
        }

        // 진행 중인 과제보다 새로운 과제가 먼저 또는 동시에 끝날 때
        // 진행 중인 과제를 새로운 과제 시작 시간까지 처리 후 교체.
        if (nextPlanStartTime <= curPlanEndTime) {
            int spendTime = nextPlanStartTime - t;
            task.playtime -= spendTime;
            t += spendTime;
            if (task.playtime <= 0) {
                answer.push_back(*task.name);
            }
            else {
                delayed.push(task);
            }
            task = pq.top(); pq.pop();
            debugLog(1, task, t, answer);
        }
        // 지연된 과제가 있을 때
        // 진행 중인 과제를 처리 후 지연된 과제로 교체.
        else if (!delayed.empty()) {
            t += task.playtime;
            task.playtime = 0;
            answer.push_back(*task.name);
            task = delayed.top(); delayed.pop();
            debugLog(2, task, t, answer);
        }
        // 새로운 과제가 있을 때
        // 진행 중인 과제를 처리 후 새로운 과제 시간까지 대기 후 새로운 과제로 교체.
        else if (!pq.empty()) {
            task.playtime = 0;
            answer.push_back(*task.name);
            t = nextPlanStartTime;
            task = pq.top(); pq.pop();
            debugLog(3, task, t, answer);
        }
        // 더 이상 추가로 할 수 있는 과제가 없을 경우
        // 진행 중인 과제를 처리 후 마무리
        else {
            t += task.playtime;
            task.playtime = 0;
            answer.push_back(*task.name);
            debugLog(4, task, t, answer);
            break;
        }
    }

    return answer;
}

int main() {
    vector<vector<string>> plans =
        {{"science", "12:40", "50"}, {"music", "12:20", "40"}, {"history", "14:00", "30"}, {"computer", "12:30", "100"}};

    vector<string> answer = solution(plans);

    cout << "===== answer =====" << endl;
    for (string ans : answer) {
        cout << ans << endl;
    }
}
