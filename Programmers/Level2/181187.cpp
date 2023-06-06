#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

// x^2 + y^2 = r^2 를 활용하여 y 가 n 일 때 나올 수 있는 두 x 의 해를 구하고
// 두 x 점 사이에 있는 정수의 갯수를 구함으로써 해당 문제를 풀어나감.
long long solution(int r1, int r2) {
	long long answer = 0;

	long long rad1pow = pow(r1, 2);
	long long rad2pow = pow(r2, 2);

	for (int i = -r2; i <= r2; ++i) {
		long long ipow = pow(i, 2);
		long long x2cnt = (long long)sqrt(rad2pow - ipow) * 2 + 1;

		if (abs(i) < r1) {
			double rad1sqrt = sqrt(rad1pow - ipow);
			long long x1 = (long long)rad1sqrt;
			long long x1cnt = x1 * 2 + 1;
			if (rad1sqrt == x1) {
				x1cnt -= 2;
			}
			answer += x2cnt - x1cnt;
		}
		else {
			answer += x2cnt;
		}
	}

	return answer;
}