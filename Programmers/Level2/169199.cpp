#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>

enum DIR { NONE, UP, RIGHT, DOWN, LEFT, END};
int dx[] = { 0, 0, 1, 0, -1 };
int dy[] = { 0, -1, 0, 1, 0 };

using namespace std;

struct Pos {
    int x, y;
    Pos(): x(-1), y(-1) {}
    Pos(int _x, int _y) : x(_x), y(_y) {}
};

Pos scale;
Pos goal;
int visited[101][101] = {};

Pos move(int x, int y, DIR dir, const vector<string> & board) {
    int curx = x, cury = y;
    int nextx = x + dx[dir], nexty = y + dy[dir];

    while (nextx >= 0 && nextx < scale.x && nexty >= 0 && nexty < scale.y && board[nexty][nextx] != 'D') {
        curx = nextx;
        cury = nexty;
        nextx = curx + dx[dir];
        nexty = cury + dy[dir];
    }

    return Pos(curx, cury);
}

int solution(vector<string> board) {
    Pos start;

    scale = Pos(board[0].size(), board.size());
    
    for (int i = 0; i < scale.y; ++i) {
        for (int j = 0; j < scale.x; ++j) {
            if (board[i][j] == 'R') {
                start.x = j;
                start.y = i;
            }
            else if (board[i][j] == 'G') {
                goal.x = j;
                goal.y = i;
            }
            visited[i][j] = 0;
        }
    }

    queue<Pos> q;
    int answer = -1;
    int cnt = 0;

    visited[start.y][start.x] = 1;
    q.push(Pos(start.x, start.y));

    while (!q.empty()) {
        int qsize = q.size();
        cnt++;
        for (int i = 0; i < qsize; ++i) {
            Pos pos = q.front(); q.pop();
            for (int dir = DIR::NONE + 1; dir < DIR::END; ++dir) {
                Pos movePos = move(pos.x, pos.y, (DIR)dir, board);
                if (visited[movePos.y][movePos.x]) continue;
                if (movePos.x == goal.x && movePos.y == goal.y) {
                    answer = cnt;
                    break;
                }
                q.push(movePos);
                visited[movePos.y][movePos.x] = 1;
            }
            if (answer != -1) break;
        }
        if (answer != -1) break;
    }

    return answer;
}

int main() {
    vector<string> board = { "...D..R", ".D.G...", "....D.D", "D....D.", "..D...." };
    int answer = solution(board);
    cout << "answer: " << answer << endl;

    return 0;
}