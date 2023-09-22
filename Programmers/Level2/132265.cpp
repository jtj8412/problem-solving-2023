#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <queue>
#include <math.h>

using namespace std;

int solution(vector<int> topping) {
    int answer = 0;
    unordered_map<int, int> left, right;
    int lSize, rSize;

    for (int i = 0; i < topping.size(); ++i) {
        int type = topping[i];
        right[type]++;
    }

    lSize = 0;
    rSize = right.size();

    for (int i = 0; i < topping.size(); ++i) {
        int type = topping[i];

        if (++left[type] == 1) {
            lSize++;
        }

        if (--right[type] == 0) {
            rSize--;
        }

        if (lSize == rSize) {
            answer++;
        }
    }

    return answer;
}