#include <bits/stdc++.h>

using namespace std;

long long target_sum = 0;

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = -2;
    long long sum1, sum2;
    queue<int> q1, q2;
    sum1 = accumulate(queue1.begin(), queue1.end(), 0);
    sum2 = accumulate(queue2.begin(), queue2.end(), 0);
    target_sum = (sum1 + sum2) / 2;
    
    for (int i = 0; i < queue1.size(); i++) {
        q1.push(queue1[i]);
        q2.push(queue2[i]);
    }
    
    int cnt = 0;
    
    while(true) {
        if (sum1 == target_sum) {
            return cnt;
        }
        else if (sum1 > target_sum) {
            int tmp = q1.front();
            q1.pop();
            q2.push(tmp);
            sum1 -= tmp;
        } else if (sum1 < target_sum) {
            int tmp = q2.front();
            q2.pop();
            q1.push(tmp);
            sum1 += tmp;
        }
        cnt++;
        
        if (cnt >= max(queue1.size(), queue2.size()) * 3) {
            return -1;
        }
    }
    return cnt;
}