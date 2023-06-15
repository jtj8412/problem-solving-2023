// 이모티콘 할인행사

#include <string>
#include <vector>
#include <iostream>

using namespace std;

const vector<int> SALE_PCT = { 10, 20, 30, 40 };

// 임의로 각 이모티콘의 할인율을 정의했을 때 도출되는 플러스 구매 인원 수 및 이모티콘 구매 가격 계산
vector<int> calc(const vector<int>& salePct, const vector<vector<int>>& users, const vector<int>& emoticons) {
    int plus = 0, buy = 0;

    for (int i = 0; i < users.size(); ++i) {
        int price = 0;

        // 특정 할인율 이상의 이모티콘을 모두 구매 시 가격 측정
        for (int j = 0; j < emoticons.size(); ++j) {
            if (users[i][0] <= salePct[j]) {
                price += emoticons[j] * (100 - salePct[j]) * 0.01;
            }
        }

        // 플러스 가입
        if (users[i][1] <= price) { 
            plus++;
        }
        // 이모티콘 구매
        else { 
            buy += price;
        }
    }

    return { plus, buy };
}

// DFS
vector<int> logic(int emoIdx, vector<int>& salePct, const vector<vector<int>>& users, const vector<int>& emoticons) {
	// 모든 이모티콘의 할인율을 임의로 정의했을 때 계산
    if (emoIdx == emoticons.size()) {
        return calc(salePct, users, emoticons);
    }

    int plus = 0, buy = 0;
    
    for (int i = 0; i < SALE_PCT.size(); ++i) {
		// emoIdx 번째 이모티콘의 할인율을 임의로 정의
        salePct[emoIdx] = SALE_PCT[i];

        vector<int> ret = logic(emoIdx + 1, salePct, users, emoticons);

		// 문제에서 지향하는 목표에 더 근접한 쪽으로 갱신
        if (ret[0] > plus || (ret[0] == plus && ret[1] > buy)) {
            plus = ret[0];
            buy = ret[1];
        }
    }

    return { plus, buy };
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> salePct(emoticons.size(), 0);
    return logic(0, salePct, users, emoticons);
}