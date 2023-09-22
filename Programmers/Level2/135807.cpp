#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <queue>
#include <math.h>

using namespace std;

int logic(const vector<int>& arr1, const vector<int>& arr2)
{
	int maxVal = *max_element(arr1.begin(), arr1.end());
	int sqrtVal = sqrt(maxVal);

	priority_queue<int> cand;

	for (int i = 1; i <= sqrtVal; ++i)
	{
		if (maxVal % i == 0)
		{
			cand.push(i);
			cand.push(maxVal / i);
		}
	}

	while (!cand.empty())
	{
		int val = cand.top();
		cand.pop();

		bool bOk = true;

		for (int j = 0; j < arr1.size(); ++j)
		{
			if (arr1[j] % val != 0)
			{
				bOk = false;
				break;
			}
		}

		if (!bOk)
		{
			continue;
		}

		for (int j = 0; j < arr2.size(); ++j)
		{
			if (arr2[j] % val == 0)
			{
				bOk = false;
				break;
			}
		}

		if (bOk) 
		{
			return val;
		}
	}

	return 0;
}

int solution(vector<int> arrayA, vector<int> arrayB) {
	int answer = max(
		logic(arrayA, arrayB),
		logic(arrayB, arrayA)
	);

	return answer;
}