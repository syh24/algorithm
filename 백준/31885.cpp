#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <set>

using namespace std;

double coin;
int n, k;
set<pair<long long, long long>> cd;
vector<pair<long long, long long>> item;
long long e[2];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};


long long dst(long long a, long long b) {
    return abs(e[0] - a) + abs(e[1] - b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        long long a, b; cin >> a >> b;
        item.push_back({a, b});
    }

    cin >> e[0] >> e[1];

    long long ans = dst(0, 0);

    for (auto x : item) {
        cd.insert({e[0]-x.first, e[1]-x.second});
    }

    for (auto cur : item) {
        //한번에 아이템써서 가는경우
        ans = min(ans, dst(cur.first, cur.second) + 2);

        //아이템 두번쓰는 경우
        if (cd.find({cur.first, cur.second}) != cd.end()) {
            ans = min(ans, 4LL);
        }

        //이동 후 아이템 쓰는 경우
        for (int i = 0; i < 4; i++) {
            long long nx = cur.first + dx[i];
            long long ny = cur.second + dy[i];

            if (cd.find({dx[i], dy[i]}) != cd.end()) {
                ans = min(ans, 3LL);
            }

            if (cd.find({nx, ny}) != cd.end()) {
                ans = min(ans, 5LL);
            }
        }
    }

    if (ans > k) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}