#include <bits/stdc++.h>

using namespace std;

int n, ar[202020], dp[202020];

int main() {
   
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> ar[i];
    } 
    dp[0] = ar[0];

    for (int i = 3; i <= n + 2; i++) {
        dp[i] = max(dp[i], dp[i-3], (ar[i-2] + ar[i-1] + ar[i]) * 2);
        dp[i] = max(dp[i], dp[i-1] + ar[i]);
    }

    cout << dp[n];

    return 0;
}