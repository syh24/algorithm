#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
n개의 퍼즐을 풀어야함
난이도: diff
현재 소요시간: time_cur
이전 소요시간: time_prev
숙련도: level

퍼즐을 제한시간내에 풀기위한 최소 숙련도 구하기!
*/

int solution(vector<int> diffs, vector<int> times, long long limit) {
    int answer = 0;
    
    int s = 1, e = 0;
    e = *max_element(diffs.begin(), diffs.end());
    while (s < e) {
        int mid = (s + e) / 2;
        long long tmp = 0;
        int prev_time = 0;
        for (int i = 0; i < diffs.size(); i++) {
            if (diffs[i] <= mid) {
                tmp += times[i];
                prev_time = times[i];
            } else {
                int df = diffs[i] - mid;
                tmp += (times[i] + prev_time) * df + times[i];
                prev_time = times[i];
            }
        }
        
        if (tmp <= limit) {
            e = mid;
        } else {
            s = mid + 1;
        }
    }
    
    return e;
}