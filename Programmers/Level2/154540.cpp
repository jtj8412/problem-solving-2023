#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

enum DIR { NONE, UP, RIGHT, DOWN, LEFT, END };

// {DIR} 방향으로 갔을 때 벡터값
const int dx[] = { 0, 0, 1, 0, -1 };
const int dy[] = { 0, -1, 0, 1, 0 };

int visited[101][101] = {}; // 중복 탐색을 막기 위함.

///////////////////////////////////////////////////////////////////////////////
// (x,y) 좌표에 있는 섬에서 길찾기를 시도하여
// 방문할 수 있는 모든 땅을 탐색하며 머무를 수 있는 기간 합산.
///////////////////////////////////////////////////////////////////////////////
int calcIsland(int x, int y, const vector<string>& maps, int w, int h) {    
    queue<pair<int, int>> q;
    int nextX, nextY, qSize;
    int day = 0;

    // 시작점 체크.
    q.push(make_pair(x, y));
    visited[y][x] = 1;
    day += (maps[y][x] - '0');
    
    // 현재 섬에서 갈 수 있는 모든 땅을 탐색.
    while (!q.empty()) {
        qSize = q.size();

        for (int i = 0; i < qSize; ++i) {
            pair<int, int> curPos = q.front(); 
            q.pop();

            for (int dir = DIR::NONE + 1; dir < DIR::END; ++dir) {
                nextX = curPos.first + dx[dir];
                nextY = curPos.second + dy[dir];

                if (nextX < 0 || nextY < 0 || nextX >= w || nextY >= h) continue; // 맵을 벗어나는 범위
                if (visited[nextY][nextX] || maps[nextY][nextX] == 'X') continue; // 이미 방문했거나 갈 수 없는 곳

                // 방문한 곳 체크 및 기간 합산.
                q.push(make_pair(nextX, nextY));
                visited[nextY][nextX] = 1;
                day += (maps[nextY][nextX] - '0');
            }
        }
    }

    return day;
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    int w = maps[0].size(), h = maps.size();

    // 맵에 있는 모든 장소 체크.
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (visited[i][j] || maps[i][j] == 'X') continue; // 이미 방문했거나 방문할 수 없는 곳.
            
            // (x, y) 좌표에 있는 섬에 머무를 수 있는 기간 계산 및 answer 에 포함.
            int day = calcIsland(j, i, maps, w, h); 
            answer.push_back(day);
        }
    }

    // answer 오름차순 정렬.
    sort(answer.begin(), answer.end());

    // 지낼 수 있는 섬이 없을 경우 '-1'
    if (answer.empty()) {
        answer.push_back(-1);
    }

    return answer;
}

int main() {
    vector<string> maps = {"X591X", "X1X5X", "X231X", "1XXX1"};

    vector<int> answer = solution(maps);

    cout << "===== answer =====" << endl;
    for (int ans : answer) {
        cout << ans << endl;
    }
}