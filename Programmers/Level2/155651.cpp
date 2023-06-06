#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

const int DAY = 60 * 24;
const int CLEANING_TIME = 10;

///////////////////////////////////////////////////////////////////////////////
// 시간을 분 단위 정수로 변환
// "05:30" -> 330
///////////////////////////////////////////////////////////////////////////////
int time2int(const string& time) {
    return (time[0] - '0') * 600 +
        (time[1] - '0') * 60 +
        (time[3] - '0') * 10 +
        (time[4] - '0');
}

///////////////////////////////////////////////////////////////////////////////
// solution
///////////////////////////////////////////////////////////////////////////////
int solution(vector<vector<string>> book_time) {
    int answer = 0;
    int length = book_time.size();
    int book_cnt[DAY + CLEANING_TIME] = {};

    for (int i = 0; i < book_time.size(); ++i) {
        int startTime = time2int(book_time[i][0]);
        int endTime = time2int(book_time[i][1]) + CLEANING_TIME; // 청소 시간 포함

        for (int j = startTime; j < endTime; ++j) {
            book_cnt[j]++;
            answer = max(answer, book_cnt[j]);
        }
    }

    return answer;
} 