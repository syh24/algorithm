#include <bits/stdc++.h>

using namespace std;

int t;

int main() {
    cin >> t;
    long long dp[1010111];

    while (t--) {
        int a; cin >> a;
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;

        for (int i = 4; i <= a; i++) {
            dp[i] = (dp[i-1] + dp[i-2] + dp[i-3]) % 1000000009;
        }

        cout << dp[a] << "\n";

    }
    

    return 0;
}