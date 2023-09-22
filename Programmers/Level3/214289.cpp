#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <math.h>
#include <stack>
#include <map>

using namespace std;

const int TEMP_MAX = 50;

bool check(int time, int temperature, int power, bool bPassenger, int t1, int t2, const vector<vector<int>>& dp) {
    // 온도 폭 체크
    if (bPassenger) {
        if (temperature < t1 || temperature > t2) {
            return false;
        }
    }
    else {
        if (temperature < 0 || temperature > TEMP_MAX) {
            return false;
        }
    }

    // 더 효율적인 온도인지 체크
    if (dp[time][temperature] != 0 && dp[time][temperature] <= power) {
        return false;
    }

    return true;
}

void processCase(int time, int temperature, int power, bool bPassenger, int t1, int t2, vector<vector<int>>& dp) {
    if (!check(time, temperature, power, bPassenger, t1, t2, dp)) {
        return;
    }

    dp[time][temperature] = power;
}

void dump1(int startTemperature, int temperature1, int temperature2) {
    cout << "start: " << startTemperature << ", temp1: " << temperature1 << ", temp2: " << temperature2 << endl;
}

void dump2(int time, const vector<vector<int>>& dp) {
    cout << "===== " << time << " =====" << endl;
    for (int i = 0; i <= TEMP_MAX; ++i) {
        int power = dp[time][i];
        if (power == 0) {
            continue;
        }
        cout << "temperature/power: " << i << "/" <<  power - 1 << endl;
    }
}

int solution(int startTemperature, int t1, int t2, int a, int b, vector<int> onboard) {
    int powerOnTempVec = (t1 - startTemperature) > 0 ? +1 : -1; // 에어컨 가동 시 온도 변화
    int powerOffTempVec = powerOnTempVec * -1; // 에어컨 종료 시 온도 변화
    vector<vector<int>> dp; // dp[time][temperature] = power

    // 온도폭 변조 ( +10 )
    startTemperature += 10;
    t1 += 10;
    t2 += 10;

    //dump1(startTemperature, t1, t2);

    // DP 초기화
    dp.resize(onboard.size());
    for (int i = 0; i < dp.size(); ++i) {
        dp[i].resize(TEMP_MAX + 1);
    }

    // 로직
    dp[0][startTemperature] = 1; // 편의상 1 으로 초기화, 추후 정답에서 -1 처리.

    int tempMin = min(t1, startTemperature);
    int tempMax = max(t2, startTemperature);

    for (int i = 1; i < onboard.size(); ++i) {
        for (int j = tempMin; j <= tempMax; ++j)
        {
            int power = dp[i - 1][j];
            if (power == 0) {
                continue;
            }

            bool bPassenger = onboard[i] == 1;

            // 1. 에어컨 가동 시
            processCase(i, j + powerOnTempVec, power + a, bPassenger, t1, t2, dp);

            // 2. 에어컨 유지 시
            processCase(i, j, power + b, bPassenger, t1, t2, dp);
            
            // 3. 에어컨 종료 시
            if (startTemperature == j) {
                processCase(i, j, power, bPassenger, t1, t2, dp);
            }
            else {
                processCase(i, j + powerOffTempVec, power, bPassenger, t1, t2, dp);
            }
        }

        //dump2(i, dp);
    }
    
    // 정답
    int answer = 0x7fffffff;

    for (int i = tempMin; i <= tempMax; ++i) {
        int power = dp[onboard.size() - 1][i];
        if (power == 0) {
            continue;
        }
        answer = min(answer, dp[onboard.size() - 1][i]);
    }

    return answer - 1;
}