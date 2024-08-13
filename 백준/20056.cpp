#include <bits/stdc++.h>
using namespace std;

int n, fm, k;

struct fire {
    int r;
    int c;
    int m;
    int s;
    int d;
};

vector<fire> ar;
int game_map[53][53];

//이동
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};


//모든 파이어볼 움직임
void move() {
    for (int i = 0; i < ar.size(); i++) {
        int tmp_x = ar[i].r + dx[ar[i].d] * ar[i].s;
        int tmp_y = ar[i].c + dy[ar[i].d] * ar[i].s;
        while(tmp_x < 0) {
            tmp_x += n;
        }
        while(tmp_y < 0) {
            tmp_y += n;
        }
        ar[i].r = tmp_x % n;
        ar[i].c = tmp_y % n;
        game_map[ar[i].r][ar[i].c] += 1;
    }
}

void check() {

    //중복 파이어볼 찾기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (game_map[i][j] >= 2) {
                int sum_m = 0, sum_s = 0;
                int check_flag = 2, dir_flag = 1;

                //파이어볼 돌면서 중복인 파이어볼 찾기
                for (int q = 0; q < ar.size(); q++) {
                    if (ar[q].r == i && ar[q].c == j) {
                        sum_m += ar[q].m;
                        sum_s += ar[q].s;
                        if (check_flag == 2) {
                            check_flag = ar[q].d % 2;
                        } else {
                            if (check_flag != ar[q].d % 2) {
                                dir_flag = 0;
                            }
                        }
                        ar.erase(ar.begin() + q);
                        q--;
                    }
                }

                int new_m = floor(sum_m / 5);
                int new_s = floor(sum_s / game_map[i][j]);
                int new_d = !dir_flag ? 1 : 0;
                if (new_m > 0) {
                    for (int y = 0; y < 4; y++) {
                        ar.push_back({i, j, new_m, new_s, new_d});
                        new_d += 2;
                    }
                }
            }
            game_map[i][j] = 0;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> fm >> k;

    for (int i = 1; i <= fm; i++) {
        int r,c,m,s,d;
        cin >> r >> c >> m >> s >> d;
        ar.push_back({r-1, c-1, m, s, d});
    }

    while (k--) {
        move();
        check();
    }

    int answer = 0;
    for (auto x : ar) {
        answer += x.m;
    }

    cout << answer;

    return 0;
}