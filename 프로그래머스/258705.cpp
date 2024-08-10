#include <bits/stdc++.h>

using namespace std;

int dp[200010];

int solution(int n, vector<int> tops) {
    int answer = 0;
    dp[0] = 1;
    dp[1] = tops[0] == 1 ? 3 : 2;
    
    for (int i = 2; i <= 2*n; i++) {
        //홀수
        if (i % 2) {
            //위에 삼각형 있는 경우
            if (tops[(i - 1) / 2]) {
                dp[i] = (dp[i-1] * 2 + dp[i-2]) % 10007;
            } else {
              //없는 경우
                dp[i] = (dp[i-1] + dp[i-2]) % 10007;
            }
        } else {
            //짝수
            dp[i] = (dp[i-1] + dp[i-2]) % 10007;
        }
    }
    
    
    return dp[2*n];
}