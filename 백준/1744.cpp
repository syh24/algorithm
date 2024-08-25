#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> pl, ms;

int main() {
    long long ans = 0;
    int zero = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        if (k > 0) {
            pl.push_back(k);
        } else if (k == 0) {
            zero++;
        } else {
            ms.push_back(k);
        }
    }

    sort(pl.begin(), pl.end());
    sort(ms.begin(), ms.end());

    //플러스 계산
    if (pl.size() % 2) {
        for (int i = pl.size() -1; i >= 1; i-=2) {
            ans += max(pl[i] * pl[i-1], pl[i] + pl[i-1]);
        }
        ans += pl[0];
    } else {
        for (int i = 0; i < pl.size(); i+=2) {
            ans += max(pl[i] * pl[i+1], pl[i] + pl[i+1]);
        }
    }
    //마이너스 계산
    if (ms.size() % 2) {
        for (int i = 0; i < ms.size()-1; i+=2) {
            ans += ms[i] * ms[i+1];
        }
        if (zero == 0) {
            ans += ms[ms.size()-1];
        }
    } else {
        for (int i = 0; i < ms.size(); i+=2) {
            ans += ms[i] * ms[i+1];
        }
    }

    cout << ans;

    return 0;
}