#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

const int CONTINOUS_DAY = 10;

bool buy(unordered_map<string, int>& want_map, const string& discount) {
    auto want_elem = want_map.find(discount);

    // 관심없는 제품
    if (want_elem == want_map.end()) {
        return false;
    }
    
    // 차감
    int remain = --want_elem->second;

    // 목표치 달성
    return (remain == 0);
}

bool restore(unordered_map<string, int>& want_map, const string& discount) {
    auto prev_elem = want_map.find(discount);

    // 관심없는 제품
    if (prev_elem == want_map.end()) {
        return false;
    }

    // 복구
    int remain = ++prev_elem->second;

    // 목표치 달성->미달성
    return (remain == 1);
}

void dump(const unordered_map<string, int>& want_map, int remain_want_type_cnt, int startDay) {
    cout << "===== " << startDay << " =====" << endl;
    cout << "remain_want_type_cnt: " << remain_want_type_cnt << endl;
    for (pair<string, int> kv : want_map) {
        cout << kv.first << " " << kv.second << endl;
    }
    cout << endl;
}

int solution(vector<string> wants, vector<int> numbers, vector<string> discounts) {
    int answer = 0;
    int remain_want_type_cnt = wants.size(); // 구매해야 하는 제품(want) 종류
    unordered_map<string, int> want_map; // 구매해야 하는 제품(want) 수량(number)
    
    // want_map 초기화
    for (int i = 0; i < wants.size(); ++i) {
        want_map[wants[i]] = numbers[i];
    }

    // 첫째 날 부터 연속 구매 시
    for (int i = 0; i < CONTINOUS_DAY; ++i) {
        if (buy(want_map, discounts[i])) {
            remain_want_type_cnt--;
        }
    }

    if (remain_want_type_cnt == 0) {
        answer++;
    }

    dump(want_map, remain_want_type_cnt, 1);

    // n번째 날 부터 연속 구매 시
    for (int i = 1; i < discounts.size() - CONTINOUS_DAY + 1; ++i) {
        // n-1번째 날에 구매했던 내역 복구
        if (restore(want_map, discounts[i - 1])) {
            remain_want_type_cnt++;
        }

        // 마지막 날 구매
        if (buy(want_map, discounts[CONTINOUS_DAY + i - 1])) {
            remain_want_type_cnt--;
        }
        
        if (remain_want_type_cnt == 0) {
            answer++;
        }

        dump(want_map, remain_want_type_cnt, i + 1);
    }

    return answer;
}