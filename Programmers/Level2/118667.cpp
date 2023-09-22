#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

int solution(vector<int> q1, vector<int> q2) {
    int answer = 0;
    int q1_idx = 0, q2_idx = 0;
    long long q1_sum = accumulate(q1.begin(), q1.end(), 0);
    long long q2_sum = accumulate(q2.begin(), q2.end(), 0);
    int maximum = q1.size() * 3; // 잘은 모르겠으나 대강 *3 이 맥시멈..
    
    while (q1_sum != q2_sum) {
        // q1 합이 더 클 때, q2 에 있는 것을 하나씩 이동
        while (q1_sum > q2_sum) {
            q1_sum -= q1[q1_idx];
            q2_sum += q1[q1_idx];        
            
            // q1 앞에 있는걸 굳이 제거하지 않고 idx 를 뒤로 이동
            // 제거할 경우 vector 특성상 높은 비용 발생
            q2.push_back(q1[q1_idx]); 
            q1_idx++;
            
            if (++answer > maximum) {
                return -1;
            }
        }
        
        // q2 합이 더 클 때, q2 에 있는 것을 하나씩 이동
        while (q2_sum > q1_sum) {
            q2_sum -= q2[q2_idx];
            q1_sum += q2[q2_idx];
            
            q1.push_back(q2[q2_idx]);
            q2_idx++;
            
            if (++answer > maximum) {
                return -1;
            }
        }
    }
    
    return answer;
}