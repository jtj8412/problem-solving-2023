#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <queue>

enum STATE { NONE = 0, O_WIN, X_WIN, PLAYING, ERROR, END };

// FOR DEBUG
enum ERROR_CODE {
    NOPE = 0,
    DUPLICATED_STATE = 1,
    INCORRECT_CNT_ON_OWIN = 2,
    INCORRECT_CNT_ON_XWIN = 3,
    INCORRECT_CNT_ON_PLAYING = 4,
};
ERROR_CODE err = ERROR_CODE::NOPE;

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// 한 라인에 대해 게임 state 갱신 여부 판단
////////////////////////////////////////////////////////////////////////////////
STATE _calcStateImpl(char ch, STATE curState) {
    STATE state = STATE::NONE;
 
    if (curState == STATE::ERROR) {
        return curState;
    }

    if (ch == 'O') {
        if (curState != STATE::NONE && curState != STATE::O_WIN) {
            return STATE::ERROR;
        }
        state = O_WIN;
    }
    else if (ch == 'X') {
        if (curState != STATE::NONE) {
            return STATE::ERROR;
        }
        state = STATE::X_WIN;
    }
    else {
        state = curState;
    }

    return state;
}

////////////////////////////////////////////////////////////////////////////////
// 게임 state 판단
////////////////////////////////////////////////////////////////////////////////
STATE calcState(const vector<string>& board) {
    STATE state = STATE::NONE;

    for (int i = 0; i < 3; ++i) {
        int h = (board[i][0] + board[i][1] + board[i][2]) / 3;
        int w = (board[0][i] + board[1][i] + board[2][i]) / 3;

        if ((state = _calcStateImpl(h, state)) == STATE::ERROR) break;
        if ((state = _calcStateImpl(w, state)) == STATE::ERROR) break;
    }

    int cl2r = (board[0][0] + board[1][1] + board[2][2]) / 3; // '\'
    int cr2l = (board[0][2] + board[1][1] + board[2][0]) / 3; // '/'

    state = _calcStateImpl(cl2r, state);
    state = _calcStateImpl(cr2l, state);

    if (state == STATE::NONE) {
        state = STATE::PLAYING;
    }

    return state;
}

////////////////////////////////////////////////////////////////////////////////
// O 와 X 의 갯수 획득
////////////////////////////////////////////////////////////////////////////////
vector<int> countOX(const vector<string>& board) {
    vector<int> cnt = { 0, 0 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 'O') cnt[0]++;
            else if (board[i][j] == 'X') cnt[1]++;
        }
    }

    return cnt;
}

int solution(vector<string> board) {
    vector<int> cnt = countOX(board);
    STATE state = calcState(board);

    if (state == STATE::O_WIN) {
        // O 가 승리했을 경우, O 는 X 보다 1 많아야 함.
        if (cnt[0] != cnt[1] + 1) {
            err = ERROR_CODE::INCORRECT_CNT_ON_OWIN;
            return 0;
        }
    }
    else if (state == STATE::X_WIN) {
        // X 가 승리했을 경우, O 는 X 와 동일해야 함.
        if (cnt[0] != cnt[1]) {
            err = ERROR_CODE::INCORRECT_CNT_ON_XWIN;
            return 0;
        }
    }
    else if (state == STATE::PLAYING) {
        // O 는 X 와 동일하거나 X 보다 1 많아야 함.
        if (cnt[0] != cnt[1] && cnt[0] != cnt[1] + 1) {
            err = ERROR_CODE::INCORRECT_CNT_ON_PLAYING;
            return 0;
        }
    }
    else {
        err = ERROR_CODE::DUPLICATED_STATE;
        return 0;
    }

    return 1;
}

int main() {
    vector<string> board = { "OOO", "XX.", "OX." };
    int answer = solution(board);

    cout << "answer: " << answer << endl;
    cout << "err: " << err << endl;

    return 0;
}