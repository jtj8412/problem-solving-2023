#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <stack>

using namespace std;

int logic(const vector<int>& elements, vector<bool> &visited, int idx)
{
    int sum = 0;
    int cnt = 0;

    for (int i = idx; i < elements.size(); i++) {
        sum += elements[i];
        if (!visited[sum]) {
            visited[sum] = true;
            cnt++;
        }
    }

    for (int i = 0; i < idx; i++) {
        sum += elements[i];
        if (!visited[sum]) {
            visited[sum] = true;
            cnt++;
        }
    }

    return cnt;
}

int solution(vector<int> elements) {
    int answer = 0;
    vector<bool> visited(1000001);

    for (int i = 0; i < elements.size(); ++i) {
        answer += logic(elements, visited, i);
    }

    return answer;
}