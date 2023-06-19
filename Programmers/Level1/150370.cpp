#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

const int DAY_PER_MONTH = 28;
const int DAY_PER_YEAR = DAY_PER_MONTH * 12; // 336

int day2num(const string& day) {
    return stoi(day.substr(0, 4)) * DAY_PER_YEAR +
        stoi(day.substr(5, 2)) * DAY_PER_MONTH +
        stoi(day.substr(8, 2));
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    map<char, int> mTerms;
    int iToday = day2num(today);

    // init mTerms.
    for (int i = 0; i < terms.size(); ++i) {
        mTerms[terms[i][0]] = stoi(terms[i].substr(2)) * DAY_PER_MONTH;
    }

    // logic.
    for (int i = 0; i < privacies.size(); ++i) {
        const string& privacy = privacies[i];
        int day = day2num(privacy);
        int term = mTerms[privacy[11]];
        if (day + term - 1 < iToday) {
            answer.push_back(i + 1);
        }
    }

    return answer;
}