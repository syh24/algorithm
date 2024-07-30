#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;

int main() {
   
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        v.push_back(a);
    } 

    sort(v.begin(), v.end());

    double ans = 0;

    for (int i = 0; i < v.size() - 1; i++) {
        double tmp = (double) v[i] / 2;
        ans += tmp;
    }

    ans += v[v.size() - 1];

    cout << ans;

    return 0;
}