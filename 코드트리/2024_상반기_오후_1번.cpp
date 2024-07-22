#include <bits/stdc++.h>
using namespace std;

int r,c,k;
int forest[80][80];
int exits[80][80];
int visited[80][80];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int sum = 0;

void init_forest() {
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 80; j++) {
            forest[i][j] = 0;
            exits[i][j] = 0;
        }
    }
}

void init_visited() {
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 80; j++) {
            visited[i][j] = 0;
        }
    }
}

void print_forest() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << forest[i][j] <<"  ";
        }
        cout << "\n";
    }   

    cout << "\n";
}

void print_exit() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << exits[i][j] <<"  ";
        }
        cout << "\n";
    }   

    cout << "\n";
}

//bfs로 탐색
int move(int x, int y) {

    int max_row = 0;

    queue<pair<int, int>> q;

    q.push({x, y});
    visited[x][y] = 1;

    while(!q.empty()) {
        pair<int, int> tmp = q.front();
        q.pop();

        max_row = max(max_row, tmp.first + 1);

        for (int i = 0; i < 4; i++) {
            int nx = tmp.first + dx[i];
            int ny = tmp.second + dy[i];

            if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
            if (visited[nx][ny] || !forest[nx][ny]) continue;
            if (forest[nx][ny] != forest[tmp.first][tmp.second] && !exits[tmp.first][tmp.second]) continue;
            visited[nx][ny] = 1;
            q.push({nx, ny});
        }
    }

    return max_row;
}

void explore_forest(int center, int exit, int gnum) {
    int first_flag = 1;
    //골렘 초기 위치
    int gx = -2;
    int gy = center;

    while(1) {
        if (gx == -2) {
            if (!forest[0][gy]) {
                gx++;
            } else {
                //좌로 회전
                if (gy != 1 && !forest[0][gy-1]) {
                    gy--;
                    gx++;
                    if (exit == 0) exit += 4;
                    exit--;
                    continue;
                }
                //우로 회전
                if (gy + 2 != c && !forest[0][gy+1]) {
                    gy++;
                    gx++;
                    if (exit == 3) exit -= 4;
                    exit++;
                    continue;
                }

                break;
            }
        } else if (gx == -1) {
            if (!forest[gx+1][gy-1] && !forest[gx+1][gy+1] && !forest[gx+2][gy]) {
                gx++;
            } else {
                //좌로 회전
                if (gy != 1 && !forest[0][gy-1]) {
                    int tmp_gy = gy - 1;
                    //아래로 이동
                    if (!forest[gx+1][tmp_gy-1] && !forest[gx+1][tmp_gy+1] && !forest[gx+2][tmp_gy]) {
                        gy--;
                        gx++;
                        if (exit == 0) exit += 4;
                        exit--;
                        continue;
                    }
                }
                //우로 회전
                if (gy + 2 != c && !forest[0][gy+1]) {
                    int tmp_gy = gy + 1;
                    //아래로 이동
                    if (!forest[gx+1][tmp_gy-1] && !forest[gx+1][tmp_gy+1] && !forest[gx+2][tmp_gy]) {
                        gy++;
                        gx++;
                        if (exit == 3) exit -= 4;
                        exit++;
                        continue;
                    }
                }

                break;
            }
        } else {
            //아래로 이동
            if (!forest[gx+1][gy-1] && !forest[gx+1][gy+1] && !forest[gx+2][gy]) {
                //맨 밑에 도달
                if (gx + 2 == r) break;
                gx++;
            } else {
                //좌로 회전
                if (gy != 1) {
                    if (!forest[gx][gy-2] && !forest[gx+1][gy-1] && !forest[gx-1][gy-1]) {
                        int tmp_gy = gy - 1;
                        //아래로 이동
                        if (gx+2 != r && !forest[gx+1][tmp_gy-1] && !forest[gx+1][tmp_gy+1] && !forest[gx+2][tmp_gy]) {
                            gy--;
                            gx++;
                            if (exit == 0) exit += 4;
                            exit--;
                            continue;
                        }
                    }
                }
                //우로 회전
                if (gy + 2 != c && !forest[gx][gy+2] && !forest[gx+1][gy+1] && !forest[gx-1][gy+1]) {
                    int tmp_gy = gy + 1;
                    //아래로 이동
                    if (gx+2 != r && !forest[gx+1][tmp_gy-1] && !forest[gx+1][tmp_gy+1] && !forest[gx+2][tmp_gy]) {
                        gy++;
                        gx++;
                        if (exit == 3) exit -= 4;
                        exit++;
                        continue;
                    }
                }
                //더이상 이동 x
                break;  
            }
        }
    }

    if (gx <= 0) {
        init_forest();
    }
    else {
        init_visited();
        forest[gx][gy] = gnum;
        forest[gx+1][gy] = gnum;
        forest[gx][gy+1] = gnum;
        forest[gx][gy-1] = gnum;
        forest[gx-1][gy] = gnum;
        exits[gx + dx[exit]][gy + dy[exit]] = 1;
        sum += move(gx, gy);
    }
}

int main() {
    cin >> r >> c >> k;
    
    for (int i = 1; i <= k; i++) {
        int a,b; 
        cin >> a;
        a--;
        cin >> b;
        explore_forest(a, b, i);
    }
    cout << sum;

    return 0;
}