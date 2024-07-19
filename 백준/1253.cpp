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

    int ans = 0;

    for (int i = 0; i < n; i++) {
        int s = 0;
        int e = n-1;

        while (s < e) {
            if (v[s] + v[e] == v[i]) {
                if (e == i) e--;
                else if (s == i) s++;
                else {
                    ans++;
                    break;
                }
            }
            else if (v[s] + v[e] > v[i]) {
                e--;
            }
            else {
                s++;
            }
        }
    }

    cout << ans;
    

    return 0;
}