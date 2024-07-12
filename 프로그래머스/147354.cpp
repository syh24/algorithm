#include <bits/stdc++.h>

using namespace std;

int idx;
int compare(vector<int> a, vector<int> b) {
    if (a[idx] == b[idx]) return a[0] > b[0];
    else return a[idx] < b[idx];
}

int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    int answer = 0;
    idx = col - 1;
    sort(data.begin(), data.end(), compare);
    
    int ans = 0;
    for (int i = row_begin - 1; i < row_end; i++) {
        int sum = 0;
        for (int j = 0; j < data[i].size(); j++) {
            sum += data[i][j] % (i+1);
        }
        if (i == row_begin - 1) ans = sum;
        else ans ^= sum;
    }
    
    
    return ans;
}