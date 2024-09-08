#include <iostream>
#include <vector>

using namespace std;

int n, k;
int w[101], v[101];
int dp[101010];

int main() {

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }

    //각 물건들을 순회
    for (int i = 0; i < n; i++) {
        //weight를 1부터 증가?
        for (int j = k; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    cout << dp[k];
    return 0;
}