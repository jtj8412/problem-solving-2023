#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <stack>

using namespace std;

int Chain(const vector<int> &cards, vector<bool>& visited, int startIdx)
{
    int chainSize = 0;
    int idx = startIdx;

    while (!visited[idx]) {
        // Visit
        visited[idx] = true;
        chainSize++;

        // Set next visit index
        idx = cards[idx] - 1;
    }

    return chainSize;
}

int solution(vector<int> cards) {
    vector<bool> visited(cards.size());
    priority_queue<int> pq;

    // Logic
    for (int i = 0; i < cards.size(); ++i) {
        if (visited[i]) {
            continue;
        }
        
        int chainSize = Chain(cards, visited, i);

        pq.push(chainSize);
    }

    // Answer
    if (pq.size() < 2) {
        return 0;
    }

    int first = pq.top();
    pq.pop();
    int second = pq.top();

    return first * second;
}