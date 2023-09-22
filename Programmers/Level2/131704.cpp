#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <stack>

using namespace std;

int solution(vector<int> orders) {
    int idx = 0, cur = 1;
    stack<int> sub;

    while (idx != orders.size())
    {
        int order = orders[idx];
        
        // 1. 메인 컨테이너 벨트로부터 전달된 상자와 실어야되는 상자가 동일할 때
        if (order == cur) {
            cur++;
            idx++;
        }
        // 2. 보조 컨테이너 벨트 맨 앞의 상자와 실어야되는 상자가 동일할 때
        else if (!sub.empty() && order == sub.top()) {
            sub.pop();
            idx++;
        }
        // 3. 현재는 처리가 불가능하여 보조 컨테이너 벨트에 적재하여야 할 때
        else if (cur < orders.size() + 1) {
            sub.push(cur++);
        }
        // 4. 더이상 처리할 수 없을 때
        else {
            break;
        }
    }

    return idx;
}