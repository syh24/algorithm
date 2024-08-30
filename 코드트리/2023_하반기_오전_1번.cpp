#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

 /*
크게 두가지 
1. 기사 이동
   - 상하좌우 이동
   - 이때 기사 있으면 연쇄적으로 밀리다가 벽이 있으면 취소
   - 사라진 기사한텐 명령 불가능
2. 대결 대미지
 - 다른 기사 밀치면 피해입음 -> w * h 직사각형 내에 놓여있는 함정 수
 - 현재 체력 이상 데미지 받으면 죽음
 - 모두 밀린 후 데미지 계산
*/

struct kisa {
    int r;
    int c;
    int h;
    int w;
    int k;
};

vector<kisa> v, ini;

int check_kisa[31];

int chess_map[45][45];

int l, n, q;
int r, c, h, w, k;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1 ,0, -1};

int kisa_num, dir;
int move_flag;

void print() {
    for (auto x : v) {
        cout << x.r << " " << x.c << " " << x.k << "\n";
    }
    cout << "\n";
}

int check_wall(int x, int y, int num) {
    for (int i = x; i < x + v[num].h; i++) {
        for (int j = y; j < y + v[num].w; j++) {
            if (i < 0 || i >= l || j < 0 || j >= l) return 1;
            if (chess_map[i][j] == 2) return 1;
        }
    }
    return 0;
}

void relay(int x, int y, int num) {

    if (check_wall(x, y, num)) {
        move_flag = 0;
        return;
    }

    for (int i = 0; i < v.size(); i++) {
        if (v[i].k <= 0) continue;
        if (check_kisa[i]) continue;
        //체크
        if (max(v[i].r, v[num].r) <= min(v[i].r + v[i].h - 1, v[num].r + v[num].h - 1)) {
            if (max(v[i].c, v[num].c) <= min(v[i].c + v[i].w - 1, v[num].c + v[num].w - 1)) {
                v[i].r += dx[dir];
                v[i].c += dy[dir];
                check_kisa[i]++;
                relay(v[i].r, v[i].c, i);
                if (!move_flag) return;
            }
        }
    }
    return;
}

void move() {
    int nx = v[kisa_num].r + dx[dir];
    int ny = v[kisa_num].c + dy[dir];

    //이동
    v[kisa_num].r = nx;
    v[kisa_num].c = ny;
    relay(nx, ny, kisa_num);
}

void damage() {

    for (int m = 0; m < v.size(); m++) {
        if (m == kisa_num) continue;
        if (check_kisa[m]==0) continue;
        int cnt = 0;
        for (int i = v[m].r; i < v[m].r + v[m].h; i++) {
            for (int j = v[m].c; j < v[m].c + v[m].w; j++) {
                if (chess_map[i][j] == 1) {
                    cnt++;
                }
            }
        }
        v[m].k -= cnt;
    }
}

int main() {

    cin >> l >> n >> q;

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++) {
            cin >> chess_map[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> r >> c >> h >> w >> k;
        r--; c--;
        v.push_back({r, c, h, w, k});
        ini.push_back({r, c, h, w, k});
    }

    for (int i = 0; i < q; i++) {
        cin >> kisa_num >> dir;
        kisa_num--;
        if (v[kisa_num].k <= 0) continue;
        vector<kisa> tmp;
        for (auto x : v) tmp.push_back(x);
        check_kisa[kisa_num]++;
        move_flag = 1;
        move();
        if (!move_flag) {
            v = tmp;
        } else {
            damage();
        }
        tmp.clear();
        memset(check_kisa, 0, sizeof(check_kisa));
    }

    int ans = 0;

    for (int i = 0; i < v.size(); i++) {
        if (v[i].k <= 0) continue;
        ans += (ini[i].k - v[i].k);
    }

    cout << ans;

    return 0;
}