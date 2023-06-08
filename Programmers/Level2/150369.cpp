#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
	long long answer = 0;
	int deli_idx = n - 1, pick_idx = n - 1, remain;

	// init xxx_idx.
	while (deli_idx >= 0 && !deliveries[deli_idx]) deli_idx--;
	while (pick_idx >= 0 && !pickups[pick_idx]) pick_idx--;

	// logic.
	while (deli_idx >= 0 || pick_idx >= 0) {
		// most right idx.
		int max_idx = max(deli_idx, pick_idx);

		// delivery for {cap} times.
		remain = cap;
		for (; deli_idx >= 0; --deli_idx) {
			int amt = min(deliveries[deli_idx], remain);
			deliveries[deli_idx] -= amt;
			remain -= amt;
			if (remain == 0) break;
		}

		// pickup for {cap} times.
		remain = cap;
		for (; pick_idx >= 0; --pick_idx) {
			int amt = min(pickups[pick_idx], remain);
			pickups[pick_idx] -= amt;
			remain -= amt;
			if (remain == 0) break;
		}

		answer += (max_idx + 1) * 2;

		// update xxx_idx.
		while (deli_idx >= 0 && !deliveries[deli_idx]) deli_idx--;
		while (pick_idx >= 0 && !pickups[pick_idx]) pick_idx--;
	}

	return answer;
}