#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

long long calc(double dval, int weightTable[]) {
    int ival = (int)dval;
    // 정수인지, 무게 한도(1000) 를 넘는지 검증.
    if (dval != ival || ival > 1000) return 0;
    // 해당 무게의 갯수 반환.
    return weightTable[ival];
}

long long solution(vector<int> weights) {
    long long answer = 0; 
    int weightTable[1001] = {};

    for (int i = 0; i < weights.size(); ++i) {        
        double dweight = (double)weights[i];

        // 아래의 값들은 해당 무게와 평행할 수 있는 값들.
        answer += calc(dweight * 2 / 2, weightTable);
        answer += calc(dweight * 3 / 2, weightTable);
        answer += calc(dweight * 4 / 2, weightTable);
        answer += calc(dweight * 2 / 3, weightTable);
        answer += calc(dweight * 4 / 3, weightTable);
        answer += calc(dweight * 2 / 4, weightTable);
        answer += calc(dweight * 3 / 4, weightTable);

        weightTable[weights[i]]++;
    }
    
    return answer;
}

int main() {
    vector<int> weights = { 100, 180, 360, 100, 270 };
    long long answer = solution(weights);

    cout << "answer: " << answer << endl;
}