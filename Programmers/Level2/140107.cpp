// 점 찍기

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

long long calcRow(long long y, long long k, long long d) {
    // x^2 + y^2 = d^2  ->  x = sqrt(d^2 - y^2)
    long long x = sqrt((d * d) - (y * y));
    return (x / k) + 1;
}

// @d : 원을 정의하는 radius 라고 가정
long long solution(int k, int d) {
    long long answer = 0;

    // y를 0부터 원의 최외곽까지 계산
    for (int i = 0; i <= d; i += k) {
        answer += calcRow(i, k, d);
    }

    return answer;
}