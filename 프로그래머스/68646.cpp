#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair < ll, ll>;
using matrix = vector<vector<ll>>;

const int MAXN = 1e6 + 10;
const int mod = 1e9 + 7;


int lefts[MAXN], rights[MAXN], ar[MAXN];

int solution(vector<int> a) {
    int answer = 0;
    int n = a.size();
    int lmn = 1e9 +11;
    int rmn = 1e9 + 11;
    for (int i = 0; i < a.size(); i++) {
        lmn = min(lmn, a[i]);
        lefts[i] = lmn;
    }
    for (int i = 0; i < a.size(); i++) {
        rmn = min(rmn, a[n - 1 - i]);
        rights[n - 1 - i] = rmn;
    }
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
        if (lefts[i] < a[i] && rights[i] < a[i]) cnt++;
    }
    
    
    return n - cnt;
}