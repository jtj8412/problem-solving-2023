#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int dx[] = {0, 1, 0, -1};
int dy[] = { -1, 0, 1, 0 };
int visited[101][101] = {};

struct Pos {
    int x = -1, y = -1;
    Pos() {}
    Pos(int _x, int _y) : x(_x), y(_y) {}
};

////////////////////////////////////////////////////////////////////////////////
// start -> goal 길찾기 함수
////////////////////////////////////////////////////////////////////////////////
int pathfind(const vector<string>& maps, Pos mapSize, Pos start, Pos goal) {
    int cost = 0;
    queue<Pos> q;

    memset((int*)visited, 0, sizeof(visited));
    q.push(start);

    while (!q.empty()) {
        int qsize = q.size();
        ++cost;

        for (int i = 0; i < qsize; ++i) {
            Pos pos = q.front(); q.pop();
            for (int j = 0; j < 4; ++j) {
                Pos nextPos(pos.x + dx[j], pos.y + dy[j]);
                // 이동 예외처리.
                // 1. 맵을 벗어나지 않도록 한다.
                // 2. 벽으로 갈 수 없도록 한다.
                // 3. 방문했던 곳을 다시 방문할 수 없도록 한다.
                if (nextPos.x < 0 || nextPos.y < 0 || nextPos.x >= mapSize.x || nextPos.y >= mapSize.y) continue;
                if (maps[nextPos.y][nextPos.x] == 'X') continue;
                if (visited[nextPos.y][nextPos.x]) continue;

                // 도착 시 길찾기 비용 리턴.
                if (nextPos.x == goal.x && nextPos.y == goal.y) return cost;

                // 방문 체크 및 다음 이동 경로를 후보에 추가. 
                visited[nextPos.y][nextPos.x] = 1;  
                q.push(nextPos);
            }
        }
    }

    // 경로가 없을 경우 -1 반환.
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
// solution
////////////////////////////////////////////////////////////////////////////////
int solution(vector<string> maps) {
    int answer = 0;
    Pos mapSize(maps[0].size(), maps.size());
    Pos start, lever, goal;

    // start, goal, lever 위치 초기화.
    for (int i = 0; i < mapSize.y; ++i) {
        for (int j = 0; j < mapSize.x; ++j) {
            char ch = maps[i][j];
            if (ch == 'S') start = Pos(j, i);
            else if (ch == 'E') goal = Pos(j, i);
            else if (ch == 'L') lever = Pos(j, i);
        }
    }

    int cost;

    // start->lever 까지의 비용 획득.
    if ((cost = pathfind(maps, mapSize, start, lever)) == -1) {
        return -1;
    }
    answer += cost;

    // lever->goal 까지의 비용 획득.
    if ((cost = pathfind(maps, mapSize, lever, goal)) == -1) {
        return -1;
    }
    answer += cost;
    
    return answer;
}

int main() {
    vector<string> maps = { "SOOOL","XXXXO","OOOOO","OXXXX","OOOOE" };
    int answer = solution(maps);

    cout << "answer: " << answer << endl;

    return 0;
}