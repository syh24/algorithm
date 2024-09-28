#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
int visited[21];
vector<int> v1, v2, l1, l2;

void combi(int idx, int sum, int len, int depth, vector<int> v) {
    if (depth == k) {
            l1.push_back(sum);
    }

    for (int i = idx + 1; i < len; i++) {
        if (visited[i]) continue;
        visited[i] = 1;
        combi(i, sum + v[i], len, depth + 1, v);
        visited[i] = 0;
    }
}

void combi2(int idx, int sum, int len, int depth, vector<int> v) {
    if (depth == k) {
            l2.push_back(sum);
    }

    for (int i = idx + 1; i < len; i++) {
        if (visited[i]) continue;
        visited[i] = 1;
        combi2(i, sum + v[i], len, depth + 1, v);
        visited[i] = 0;
    }
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m >> k;

        for (int i = 0; i < n; i++) {
            int a; cin >> a;
            v1.push_back(a);
        }

        for (int i = 0; i < m; i++) {
            int a; cin >> a;
            v2.push_back(a);
        }

        for (int i = 0; i < n; i++) {
            combi(i, v1[i], n, 1, v1);
        }

        for (int i = 0; i < m; i++) {
            combi2(i, v2[i], m, 1, v2);
        }

        sort(l1.begin(), l1.end());
        sort(l2.begin(), l2.end());
        int len1 = l1.size();
        int len2 = l2.size();
        int mx = max(abs(l1[len1 - 1] - l2[0]), abs(l2[len2 - 1] - l1[0]));

        int x = 0;
        int y = 0;
        int mn = abs(l1[x] - l2[y]);
        while (x < len1 && y < len2) {
            int tmp = abs(l1[x] - l2[y]);
            mn = min(mn, tmp);

            if (l1[x] > l2[y]) {
                y++;
            }
            else if (l1[x] < l2[y]) {
                x++;
            }
            else {
                mn = 0;
                break;
            }
        }


        cout << mn << " " << mx << "\n";

        v1.clear();
        v2.clear();
        l1.clear();
        l2.clear();
    }

}