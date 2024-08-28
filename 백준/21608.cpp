#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
vector<int> v;

int cls[22][22];
int likes[410][410];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};


void organize(int st) {
    int g_lk_cnt = -1;
    int g_empty_cnt = -1;
    int x,y;
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cls[i][j]) continue;
            int lk_cnt = 0;
            int empty_cnt = 0;
            for (int p = 0; p < 4; p++) {
                int nx = i + dx[p];
                int ny = j + dy[p];

                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

                if (cls[nx][ny]) {
                    if (likes[st][cls[nx][ny]] == 1) {
                        lk_cnt++;
                    }
                } else {
                    empty_cnt++;
                }
            }

            if (g_lk_cnt < lk_cnt) {
                x = i;
                y = j;
                g_lk_cnt = lk_cnt;
                g_empty_cnt = empty_cnt;
            } else if (g_lk_cnt == lk_cnt) {
                if (g_empty_cnt < empty_cnt) {
                    x = i;
                    y = j;
                    g_lk_cnt = lk_cnt;
                    g_empty_cnt = empty_cnt;
                }
            }
        }
    }

    cls[x][y] = st;
}

int main() {
    cin >> n;

    for (int i = 0; i < pow(n, 2); i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        v.push_back(a);
        likes[a][b] = 1;
        likes[a][c] = 1;
        likes[a][d] = 1;
        likes[a][e] = 1;
    }

    for (auto x : v) {
        organize(x);
    }
    
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int tmp = 0;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (likes[cls[i][j]][cls[nx][ny]] == 1) tmp++;
            }

            if (tmp == 3) {
                ans += 100;
            } else if (tmp == 4) {
                ans += 1000;
            } else if (tmp == 2){
                ans += 10;
            } else {
                ans += tmp;
            }
        }
    }

    cout << ans;
    
    return 0;
}