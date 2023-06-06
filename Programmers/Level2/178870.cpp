#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define INT_MAX 2147483647

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
	vector<int> answer = { -1, -1 };
	int sum = 0, cnt = 0;
	int minCnt = INT_MAX;
	int left, right = sequence.size() - 1;

	for (int i = sequence.size() - 1; i >= 0; --i) {
		sum += sequence[i];
		left = i;
		cnt++;

		if (sum > k) {
			sum -= sequence[right];
			cnt--;
			right--;
		}

		if (sum == k) {
			if (minCnt < cnt) {
				break;
			}
			else {
				minCnt = cnt;
				answer[0] = left;
				answer[1] = right;
			}
		}
	}

	return answer;
}

int main() {
	// input //
	vector<int> sequence = { 2, 2, 2, 2, 2 };
	int k = 6;

	cout << "===== answer =====" << endl;

	// answer 
	// cout << solution(sequence, k) << endl;

	// answer (vector)
	auto answer = solution(sequence, k);
	for (auto ans : answer) {
		cout << ans << endl;
	}

	return 0;
}
