#include <bits/stdc++.h>
using namespace std;

/*
게임은 M턴 -> 매 턴마다 루돌프와 산타가 움직임 -> BFS
1. 루돌프가 먼저 움직임 (거리 계산 후 가장 가까운 산타에게 1칸 돌진)
2. 1번 ~ P번 산타가 순서대로 움직임

루돌프 -> 8방향으로 이동 가능
산타 -> 4방향으로 이동 가능 상 > 우 > 하 > 좌

충돌:
루돌프가 움직여 충돌 -> 산타 C점 얻고 루돌프가 이동해온 방향으로 C칸 만큼 밀려남
산타가 움직여 충돌 -> 산타 자신이 이동해온 반대 방향으로 D칸 만큼 밀려남

상호작용:
밀려났을 때 그 칸에 산타가 있으면 그 방향으로 산타가 연쇄적으로 밀려남

기절:
산타와 루돌프가 충돌을하면 기절을 하게 됨 k턴에 충돌 -> k+2턴에 다시 정상
기절중에도 상호작용은 가능하고, 루돌프가 기절상태의 산타를 돌진 대상으로 선택 가능

게임 종료:
모든 산타가 게임 아웃되거나 M턴이 끝나거나!
각 산타가 얻은 점수를 출력하면 됨
*/


int n,m,p,d,pc,r,c;
int game_out_cnt = 0;
vector<pair<int, int>> santa_loc(51);
int santa[51][51];

//루돌프 움직임
int rx[8] = {-1,-1,-1,0,0,1,1,1};
int ry[8] = {-1,0,1,-1,1,-1,0,1};

//산타 움직임
int sx[4] = {-1, 0, 1, 0};
int sy[4] = {0, 1, 0, -1};
int stun[31], game_out[31], score[31];

void print_map() {
    cout << r << " " << c << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << santa[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void is_game_out() {
    if (game_out_cnt == p) {
        for (int i = 1; i <= p; i++) {
            cout << score[i] << " ";
        }
        exit(0);
    }
}

bool checkGameRange(int x, int y) {
    if (0>x || x >= n || y < 0 || y >= n) return true;
    return false;
}

void interactionBySanta(int x, int y, int dir, int santa_num) {
    //다른 산타가 있으면
    while (true) {
        santa_loc[santa_num].first = x;
        santa_loc[santa_num].second = y;
        if (santa[x][y]) {
            int tmp = santa[x][y];
            santa[x][y] = santa_num;
            santa_num = tmp;

            x += sx[dir];
            y += sy[dir];
            if (checkGameRange(x, y)) {
                game_out[santa_num] = 1;
                game_out_cnt++;
                is_game_out();
                break;
            }
        } else {
            santa[x][y] = santa_num;
            break;
        }
    }
}

void interactionByRudolf(int x, int y, int dir, int santa_num) {
    //다른 산타가 있으면
    while (true) {
        santa_loc[santa_num].first = x;
        santa_loc[santa_num].second = y;
        if (santa[x][y]) {
            int tmp = santa[x][y];
            santa[x][y] = santa_num;
            santa_num = tmp;

            x += rx[dir];
            y += ry[dir];
            if (checkGameRange(x, y)) {
                game_out[santa_num] = 1;
                game_out_cnt++;
                is_game_out();
                break;
            }
        } else {
            santa[x][y] = santa_num;
            break;
        }
    }
}

void move_santa() {
    for (int i = 1; i <= p; i++) {
        //기절 또는 탈락 했으면
        if (stun[i] || game_out[i]) continue;
        int x = santa_loc[i].first;
        int y = santa_loc[i].second;
        //현재 거리 계산
        int dist_now = pow(x-r, 2) + pow(y-c, 2);

        int dist = 1e6;
        int move_x, move_y, move_dir;
        int move_flag = 0;

        for (int j = 0; j < 4; j++) {
            int nx = x + sx[j];
            int ny = y + sy[j];
            //게임판 벗어나면
            if (checkGameRange(nx, ny)) continue;
            //다른 산타가 있는 경우
            if (santa[nx][ny]) continue;
            //가까워질 방법이 없으면
            if (dist_now <= pow(nx-r,2)+pow(ny-c,2)) continue;

            if (pow(nx-r,2)+pow(ny-c,2) < dist) {
                dist = pow(nx-r,2) + pow(ny-c, 2);
                move_x = nx;
                move_y = ny;
                move_dir = j;
                move_flag = 1;
            }
        }

        //이동해야할 곳을 못찾음
        if (!move_flag) continue;

        santa[x][y] = 0;
        // 이동해야할 곳을 찾음
        //루돌프와 충돌이 일어났을 경우
        if (move_x == r && move_y == c) {
            //충돌 로직 작성
            score[i] += d;
            stun[i] = 2;
            move_dir = (move_dir+2)%4;
            move_x += sx[move_dir] * d;
            move_y += sy[move_dir] * d;
            //게임판 밖으로 튕겨나갔다면
            if (checkGameRange(move_x, move_y)) {
                game_out[i] = 1;
                game_out_cnt++;
                is_game_out();
            } else {
                interactionBySanta(move_x, move_y, move_dir, i);
            }
        } else {
            santa_loc[i].first = move_x;
            santa_loc[i].second = move_y;
            santa[move_x][move_y] = i;
        }
    }
}

void move_rudolf() {
    int dist = 1e6;
    int nx ,ny;

    //가장 가까운 산타 위치 구해주기
    for (int i = 1; i <= p; i++) {
        if (game_out[i]) continue;
        int tx = santa_loc[i].first;
        int ty = santa_loc[i].second;
        if (dist >= (pow(tx-r, 2)+ pow(ty-c, 2))) {
            if (dist == (pow(tx-r, 2)+ pow(ty-c, 2))) {
                if (tx > nx || (tx == nx && ty > ny)) {
                    dist = pow(tx-r, 2)+ pow(ty-c, 2);
                    nx = tx; ny = ty;
                }
                continue;
            }
            dist = pow(tx-r, 2)+ pow(ty-c, 2);
            nx = tx; ny = ty;
        }
    }

    int k;
    dist = 1e5;
    // 가장 우선순위가 높은 산타를 향해 돌진
    for (int i = 0; i < 8; i++) {
        int tx = r + rx[i];
        int ty = c + ry[i];

        if (dist >= (pow(nx-tx,2) + pow(ny-ty, 2))) {
            dist = pow(nx-tx,2) + pow(ny-ty, 2);
            k = i;
        }
    }
    //루돌프 이동
    r += rx[k];
    c += ry[k];

    // 루돌프 이동한 곳에 산타가 있다면
    if (santa[r][c]) {
        int santa_num = santa[r][c];
        score[santa_num] += pc;
        stun[santa_num] = 2;
        int move_x = r + rx[k] * pc;
        int move_y = c + ry[k] * pc;
        santa[r][c] = 0;
        if (checkGameRange(move_x, move_y)) {
            game_out[santa_num] = 1;
            game_out_cnt++;
            is_game_out();
        } else {
            interactionByRudolf(move_x, move_y, k, santa_num);
        }
    }
    
}

int main() {
    cin >> n >> m >> p >> pc >> d;

    //루돌프 초기 위치
    cin >> r >> c;
    r--; c--;

    for (int i = 1; i <= p; i++) {
        int stnum,x,y; cin >> stnum >> x >> y;
        santa[x-1][y-1] = stnum;
        santa_loc[stnum] = {x-1, y-1};
    }

    //m턴만큼 게임 진행
    while (m--) {
        move_rudolf();
        move_santa();
        is_game_out();
        for (int i = 1; i <= p; i++) {
            if (stun[i]>0) stun[i]--;
        }
        for (int i = 1; i <= p; i++) {
            if (game_out[i] > 0) continue;
            score[i]++;
        }
    }
    for (int i = 1; i <= p; i++) {
        cout << score[i] << " ";
    }
    return 0;
}