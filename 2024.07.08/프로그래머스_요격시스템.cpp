#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int cmp (vector<int> a, vector<int> b) {
    return a[1] < b[1];
}

int solution(vector<vector<int>> targets) {
    int answer = 0;
    sort(targets.begin(), targets.end(), cmp);
    
    int last = -1;
    
    for (auto x : targets) {
        if (x[0] < last) {
            continue;
        } else {
            answer++;
            last = x[1];
        }
    }
    
    return answer;
}