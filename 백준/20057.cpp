#include <bits/stdc++.h>
using namespace std;

int n;
int ar[510][510];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int answer = 0;

void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ar[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool checkRange(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) return false;

    return true;
}

void cal_sand(int nx, int ny, int r, int c, int dir) {

    int prev_dir = dir-1;
    if (prev_dir < 0) prev_dir += 4;
    int next_dir = (dir + 1) % 4;
    int sand_amount = ar[nx][ny];
    
    //1퍼센트 애들부터 계산
    int one_percent = floor(sand_amount * 0.01);
    if (one_percent) {
        if (checkRange(r + dx[prev_dir], c + dy[prev_dir])) {
            ar[r + dx[prev_dir]][c + dy[prev_dir]] += one_percent;
        } else {
            answer += one_percent;
        }
        if (checkRange(r + dx[next_dir], c + dy[next_dir])) {
            ar[r + dx[next_dir]][c + dy[next_dir]] += one_percent;
        } else {
            answer += one_percent;
        }
    }

    //7퍼센트 애들
    int seven_percent = floor(sand_amount * 0.07);
    if (seven_percent) {
        if (checkRange(nx + dx[prev_dir], ny + dy[prev_dir])) {
            ar[nx + dx[prev_dir]][ny + dy[prev_dir]] += seven_percent;
        } else {
            answer += seven_percent;
        }

        if (checkRange(nx + dx[next_dir], ny + dy[next_dir])) {
            ar[nx + dx[next_dir]][ny + dy[next_dir]] += seven_percent;
        } else {
            answer += seven_percent;
        }
    }

    //2퍼센트 애들
    int second_percent = floor(sand_amount * 0.02);
    if (second_percent) {
        if (checkRange(nx + dx[prev_dir] * 2, ny + dy[prev_dir] * 2)) {
            ar[nx + dx[prev_dir] * 2][ny + dy[prev_dir] * 2] += second_percent;
        } else {
            answer += second_percent;
        }

        if (checkRange(nx + dx[next_dir] * 2, ny + dy[next_dir] * 2)) {
            ar[nx + dx[next_dir] * 2][ny + dy[next_dir] * 2] += second_percent;
        } else {
            answer += second_percent;
        }
    }

    //10퍼센트 애들
    int ten_percent = floor(sand_amount * 0.1);
    if (ten_percent) {
        if (checkRange(nx + dx[prev_dir] + dx[dir], ny + dy[prev_dir] + dy[dir])) {
            ar[nx + dx[prev_dir] + dx[dir]][ny + dy[prev_dir] + dy[dir]] += ten_percent;
        } else {
            answer += ten_percent;
        }

        if (checkRange(nx + dx[next_dir] + dx[dir], ny + dy[next_dir] + dy[dir])) {
            ar[nx + dx[next_dir] + dx[dir]][ny + dy[next_dir] + dy[dir]] += ten_percent;
        } else {
            answer += ten_percent;
        }
    }

    //5퍼센트 애들
    int five_percent = floor(sand_amount * 0.05);
    if (five_percent) {
        if (checkRange(nx + dx[dir] * 2, ny + dy[dir] * 2)) {
            ar[nx + dx[dir] * 2][ny + dy[dir] * 2] += five_percent;
        } else {
            answer += five_percent;
        }
    }

    //남은 애들
    int rest_amount = sand_amount - (one_percent * 2 + seven_percent * 2 + second_percent * 2 + ten_percent * 2 + five_percent);
    if (rest_amount) {
        if (checkRange(nx + dx[dir], ny + dy[dir])) {
            ar[nx + dx[dir]][ny + dy[dir]] += rest_amount;
        } else {
            answer += rest_amount;
        }
    }
    ar[nx][ny] = 0;
}

int main()
{
    
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ar[i][j];
        }
    }

    int r = n / 2;
    int c = n / 2;

    int clock = 0, len = 1, dir = 0;

    while(1) {
        if (r <= 0 && c <= 0) break;

        if (clock == 2) {
            clock = 0;
            len++;
        }
        for (int i = 0; i < len; i++) {
            int nr = r + dx[dir];
            int nc = c + dy[dir];
            if (ar[nr][nc] != 0) {
                cal_sand(nr, nc, r, c, dir);
            }
            r = nr;
            c = nc;
        }
        clock++;
        dir += 1;
        dir %= 4;
    }


    cout << answer;

    return 0;
}