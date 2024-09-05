#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

struct task {
    string name;
    int play;
};

stack<task> st;

int cmp(vector<string> &a, vector<string> &b) {
    return a[1] < b[1];
}

int convertTime(string t) {
    int ret = 0;
    ret += stoi(t.substr(0, 2)) * 60;
    ret += stoi(t.substr(3, 5));
    return ret;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    sort(plans.begin(), plans.end(), cmp);
    vector<string> prev;
    
    for(auto x : plans) {
        if (!prev.empty()) {
            if (convertTime(prev[1]) + stoi(prev[2]) > convertTime(x[1])) {
                int rt = convertTime(prev[1]) + stoi(prev[2]) - convertTime(x[1]);
                st.push({prev[0], rt});
                prev = x;
            } else {
                answer.push_back(prev[0]);
                int now = convertTime(prev[1]) + stoi(prev[2]);
                if (now == convertTime(x[1])) {
                    prev = x;
                } else {
                    int rest = convertTime(x[1]) - now;
                    while(!st.empty()) {
                        auto tmp = st.top();
                        st.pop();
                        if (tmp.play > rest) {
                            st.push({tmp.name, tmp.play-rest});
                            break;
                        }
                        answer.push_back(tmp.name);
                        rest -= tmp.play;
                    }
                }
            }
        }
        prev = x;
    }
    answer.push_back(prev[0]);
    while(!st.empty()) {
        auto tmp = st.top();
        st.pop();
        answer.push_back(tmp.name);
    }
    
    return answer;
}