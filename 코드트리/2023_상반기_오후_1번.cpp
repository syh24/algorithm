#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

/*
참가자
1. 빈칸으로 상하 > 좌우 움직일 수 있음
2. 항상 출구보다 가까운 쪽으로 이동할 수 있음
3. 움직일 수 없으면 안움직임
4. 한칸에 2명이상 가능

미로 회전
참가자와 출구를 포함한 가장 작은 정사각형이 회전함
*/

int n, m, k;
int maze[20][20];

//0, 1이 좌표, 2가 탈출여부
int people[13][4];
int ext[2];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int mv_cnt = 0;

void print() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << maze[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_people() {
    for (int i = 0; i < m; i++) {
        cout << people[i][0] << " " << people[i][1];
        cout << "\n";
    }
    cout << ext[0] << " " << ext[1] << "\n";
}

void move(int x) {

    int mn_dist = abs(ext[0] - people[x][0]) + abs(ext[1] - people[x][1]);
    int tx = people[x][0], ty = people[x][1];

    for (int i = 0; i < 4; i++) {
        int nx = people[x][0] + dx[i];
        int ny = people[x][1] + dy[i];
        //미로 밖 or 벽
        if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
        if (maze[nx][ny] > 0) continue;
        //min 계산
        int dist = abs(ext[0] - nx) + abs(ext[1] - ny);
        if (dist == 0) {
            mv_cnt++;
            people[x][0] = nx;
            people[x][1] = ny;
            people[x][2] = 1;
            return;
        }

        if (dist < mn_dist) {
            mn_dist = dist;
            tx = nx;
            ty = ny;
        }
    }

    //실제 이동
    if (tx != people[x][0] || ty != people[x][1])
        mv_cnt++;
    people[x][0] = tx;
    people[x][1] = ty;
    return;
}

void rotate(int len, int x, int y) {
    int tmp[13][13];

    //복사본
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            tmp[i][j] = maze[i][j];
        }
    }
    
    for (int j = x; j <= x + len; j++) {
        for (int i = y; i <= y + len; i++) {
            //x,x+1, x+2, y + k에 고정
            maze[x + i - y][len + y - j + x] = tmp[j][i];
        }
    }

    //벽 내구도 깎기
    for (int j = x; j <= x + len; j++) {
        for (int i = y; i <= y + len; i++) {
            if (maze[j][i] > 0) maze[j][i]--;
        }
    }

    //참가자 돌리기
    for (int i = 0; i < m; i++) {
        if (people[i][2] > 0) continue;
        if (x <= people[i][0] && people[i][0] <= x + len && y <= people[i][1] && people[i][1] <= y + len) {
            int ox = people[i][0] - x;
            int oy = people[i][1] - y;
            int rx = oy, ry = len - ox;
            people[i][0] = rx + x;
            people[i][1] = ry + y;
        }
    }

    //출구 돌리기
    if (x <= ext[0] && ext[0] <= x + len && y <= ext[1] && ext[1] <= y + len) {
        int ox = ext[0] - x;
        int oy = ext[1] - y;
        int rx = oy, ry = len - ox;
        ext[0] = rx + x;
        ext[1] = ry + y;
    }
}

int check(int x, int y, int l) {

    for (int i = 0; i < m; i++) {
        if (people[i][2] > 0) continue;
        //출구 있고
        if (x <= ext[0] && ext[0] <= x + l &&  y <= ext[1] && ext[1] <= y + l) {
            //참가자 있고
            if (x <= people[i][0] && people[i][0] <= x + l &&  y <= people[i][1] && people[i][1] <= y + l) {
                return 1;
            }
        }
    }
    return 0;
}

void get_square() {
    for (int len = 1; len < n; len++) {
        for (int i = 1; i <= n - len; i++) {
            for (int j = 1; j <= n - len; j++) {
                //참가자 있으면
                if (check(i, j, len)) {
                    rotate(len ,i, j);
                    return;
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> k;

    //미로
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> maze[i][j];
        }
    }

    //참가자
    for (int i = 0; i < m; i++) {
        cin >> people[i][0] >> people[i][1];
    }

    //출구
    cin >> ext[0] >> ext[1];

    //게임 시작
    while (k--) {
        for (int i = 0; i < m; i++) {
            if (people[i][2] == 1) continue;
            move(i);
        }
        get_square();
    }

    cout << mv_cnt << "\n";
    cout << ext[0] << " " << ext[1];

    return 0;
}