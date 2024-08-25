#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

/*
공격력이 0 이하가 되면 부서짐, 최초에 부서진 포탑이 존재할 수도 있음
4가지 액션 순서대로 수행 -> k번 반복
1. 공격자 선정
 - 가장 약한 포탑 선정
 - 공격력 낮고, 최근에 공격한 포탑, 열값이 큰 포탑

2. 공격자의 공격
 - 가장 강한 포탑 공격
 - 공격력 가장 높고, 공격한지 가장 오래된 포탑, 열값이 작은 포탑
  1. 레이저 공격
    - 우/하/좌/상 순으로 탐색해서 공격
    - 최단 경로 없으면 포탄 공격 진행
  2. 포탄 공격
    - 공격대상과 주위 8군데 모두 피해
3. 포탑 부서진
 - 공격력이 0 이하가 된 포탑은 부서짐
4. 포탑 정비
 - 공격자나 공격당한 포탑이 아닌 애들은 공격력이 1씩 오름
*/

int n, m, k, dist;
int game_map[11][11], attack_count[11][11], participant[11][11], visited[11][11];
pair<int, int> atker, target;
int answer_flag = 0;
int atk_cnt = 1;

//탐색
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int sx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
int sy[8] = {1, -1, -1, 0, 1, -1, 0, 1};

int lazer_flag = 0;
vector<pair<int, int> > lpath;

int back_x[11][11], back_y[11][11];


void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << game_map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            participant[i][j] = 0;
        }
    }
}

void init_visited() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = 0;
        }
    }
}

//강한 포탑 찾기
void find_strong_tower() {
    int last_atk = 1001;
    int mx_atk = -1;

    for (int j = m - 1; j >= 0; j--) {
        for (int i = n - 1; i >= 0; i--) {
            if (!game_map[i][j]) continue;
            if (i == atker.first && j == atker.second && !answer_flag) continue;
            //공격력이 크면   
            if (mx_atk <= game_map[i][j]) {
                //최근에 공격했는지 체크
                if (mx_atk < game_map[i][j]) {
                    mx_atk = game_map[i][j];
                    last_atk = attack_count[i][j];
                    target = {i, j};
                } else {
                    if (attack_count[i][j] < last_atk) {
                        //열값이 작으면 계속 갱신되도록
                        mx_atk = game_map[i][j];
                        last_atk = attack_count[i][j];
                        target = {i, j};
                    } else if (attack_count[i][j] == last_atk) {
                        if (target.first + target.second > i + j) {
                            mx_atk = game_map[i][j];
                            last_atk = attack_count[i][j];
                            target = {i, j};
                        } else if (target.first + target.second == i + j) {
                            if (target.second > j) {
                                mx_atk = game_map[i][j];
                                last_atk = attack_count[i][j];
                                target = {i, j};
                            }
                        }
                    }
                }
            }
        }
    }
    participant[target.first][target.second] = 1;
}

//약한 포탑 찾기
void find_attacker() {
    int last_atk = -1;
    int min_atk = 5001;

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (!game_map[i][j]) continue;
            //공격력이 작으면   
            if (min_atk >= game_map[i][j]) {
                //최근에 공격했는지 체크
                if (min_atk > game_map[i][j]) {
                    min_atk = game_map[i][j];
                    last_atk = attack_count[i][j];
                    atker = {i, j};
                } else {
                    if (attack_count[i][j] > last_atk) {
                        //열값이 크면 계속 갱신되도록
                        min_atk = game_map[i][j];
                        last_atk = attack_count[i][j];
                        atker = {i, j};
                    } else if (attack_count[i][j] == last_atk) {
                        if (atker.first + atker.second < i + j) {
                            min_atk = game_map[i][j];
                            last_atk = attack_count[i][j];
                            atker = {i, j};
                        } else if (atker.first + atker.second == i + j) {
                            if (atker.second < j) {
                                min_atk = game_map[i][j];
                                last_atk = attack_count[i][j];
                                atker = {i, j};
                            }
                        }
                    }
                }
            }
        }
    }
    participant[atker.first][atker.second] = 1;
    attack_count[atker.first][atker.second] = atk_cnt;
    atk_cnt++;
}

int get_distance() {
   return min(abs(atker.first - target.first), abs(n - atker.first + target.first)) + min(abs(atker.second - target.second), abs(m-atker.second + target.second));
}

void find_path_for_lazer() {
    //find by bfs
    queue<pair<int, int>> q;
    q.push({atker.first, atker.second});

    while(!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        if (cx == target.first && cy == target.second) {
            lazer_flag = 1;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = (cx + dx[i] + n) % n;
            int ny = (cy + dy[i] + m) % m;
            if (!game_map[nx][ny]) continue;
            if (!visited[nx][ny]) {
                visited[nx][ny] = 1;
                back_x[nx][ny] = cx;
                back_y[nx][ny] = cy;
                q.push({nx, ny});
            }
        }
    }
    
}

void attack() {
    //공격할 대상 찾자
    find_strong_tower();

    if (!game_map[target.first][target.second]) return;

    //레이저 공격
    lazer_flag = 0;
    dist = get_distance();
    lpath.clear();
    init_visited();
    find_path_for_lazer();

    game_map[atker.first][atker.second] += n + m;
    int atk_lev = game_map[atker.first][atker.second];
    if (lazer_flag) {
        game_map[target.first][target.second] -= atk_lev;
        int cx = back_x[target.first][target.second];
        int cy = back_y[target.first][target.second];
        while (!(atker.first == cx && atker.second == cy)) {
            game_map[cx][cy] -= (atk_lev / 2);
            participant[cx][cy] = 1;
            int nx = back_x[cx][cy];
            int ny = back_y[cx][cy];
            cx = nx;
            cy = ny;
        }  
    } else {
        //대포 공격
        game_map[target.first][target.second] -= atk_lev;
        for (int i = 0; i < 8; i++) {
            int nx = target.first + sx[i];
            int ny = target.second + sy[i];
            nx = nx < 0 ? nx + n : nx;
            ny = ny < 0 ? ny + m : ny;
            nx %= n;
            ny %= m;
            if (!game_map[nx][ny]) continue;
            if (nx == atker.first && ny == atker.second) continue;
            game_map[nx][ny] -= (atk_lev / 2);
            participant[nx][ny] = 1;
        }
    }
}

//포탑 부수기
void destroy() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (game_map[i][j] < 0) {
                game_map[i][j] = 0;
            }
        }
    }
}

//포탑 정비 공격력 증가
void repair() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!game_map[i][j] || participant[i][j] > 0) continue;
            game_map[i][j] += 1;
        }
    }
}

int main() {
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> game_map[i][j];
        }
    }

    while (k--) {
        //게임 진행
        find_attacker();
        attack();
        destroy();
        repair();
        init();
    }

    int answer = 0;
    answer_flag = 1;
    find_strong_tower();
    cout << game_map[target.first][target.second];

    return 0;
}