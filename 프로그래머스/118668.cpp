#include <bits/stdc++.h>

using namespace std;

/*
코딩력, 알고력이 있음
이 둘을 가지고 문제를 풀 수 있는지 없는지를 체크
모든 문제를 풀 수 있는 최단 시간을 구해야 함.

아예 감이 안오는디? -> 모든 경우 탐색?

DP로 풀이
알고력, 코딩력을 가지고 dp값은 걸리는 시간을 구해줌
*/


int dp[300][300];

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 1e7;
    int mx_alp = alp,mx_cop = cop;
    for(auto x : problems) {
        mx_alp = max(mx_alp, x[0]);
        mx_cop = max(mx_cop, x[1]);
    }
    
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
            dp[i][j] = 1e7;
        }
    }
    
    dp[alp][cop] = 0;
    
    for (int i = alp; i <= mx_alp; i++) {
        for (int j = cop; j <= mx_cop; j++) {
            if (i < mx_alp)
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);
            if(j < mx_cop)
                dp[i][j+1] = min(dp[i][j+1], dp[i][j] + 1);

            for (int k = 0; k < problems.size(); k++) {
                if (problems[k][0] <= i && problems[k][1] <= j) {
                    int tmp_alp = problems[k][2];
                    int tmp_cop = problems[k][3];
                    int nx = min(i+tmp_alp, mx_alp);
                    int ny = min(j+tmp_cop, mx_cop);
                    dp[nx][ny] = min(dp[nx][ny], dp[i][j] + problems[k][4]); 
                }
            }
        }
    }
    
    answer = dp[mx_alp][mx_cop];
    
    return answer;
}