#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string t, string p) {
    int answer = 0;
    int size = p.size();
    long long pval = stoll(p);

    for (int i = 0; i <= t.size() - size; ++i) {
        long long tval = stoll(t.substr(i, size));
        if (pval >= tval) {
            answer++;
        }
    }

    return answer;
}