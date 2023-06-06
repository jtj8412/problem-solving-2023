#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool compare(vector<int> a, vector<int> b) {
	return a[0] < b[0];
}

int solution(vector<vector<int>> targets) {
	int answer = 0;
	int prev = -1;

	sort(targets.begin(), targets.end(), compare);

	for (int i = 0; i < targets.size(); ++i) {
		vector<int>& target = targets[i];
		if (prev <= target[0]) {
			prev = target[1];
			answer++;
		}
		else {
			prev = min(prev, target[1]);
		}
	}

	return answer;
}

int main() {
	vector<vector<int>> targets = 
		{{4, 5}, {4, 8}, {10, 14}, {11, 13}, {5, 12}, {3, 7}, {1, 4}};

	cout << solution(targets) << endl;

	return 0;
}