// 테이블 해시 함수

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int COL_IDX;

// 튜플 정렬
bool compare(const vector<int>& a, const vector<int>& b) {
    if (a[COL_IDX] == b[COL_IDX]) {
        return a[0] > b[0];
    }
    return a[COL_IDX] < b[COL_IDX];
}

// 튜플(S_row) 계산
int calcValue(const vector<int> v, int row) {
    int val = 0;
    for (int i = 0; i < v.size(); ++i) {
        val += v[i] % row;
    }
    return val;
}

int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    int answer = 0;
    COL_IDX = col - 1;

    // 튜플 정렬
    sort(data.begin(), data.end(), compare);

    // 각 튜플을 계산하면서 xor 연산
    answer = calcValue(data[row_begin - 1], row_begin);
    for (int i = row_begin; i < row_end; ++i) {
        answer ^= calcValue(data[i], i + 1);
    }

    return answer;
}