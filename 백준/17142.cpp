#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m, ar[55][55];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

vector<pair<int, int>> v, tmp;

struct virus {
    int x;
    int y;
    int time;
};

int answer = 1000000;

void bfs() {
    int visited[55][55] = {0, };
    queue<virus> q;
    int time = -1;

    for (auto t : tmp) {
        visited[t.first][t.second] = 1;
        q.push({t.first, t.second, 0});
    }

    while (!q.empty()) {
        auto k = q.front();
        q.pop();
        time = max(time, k.time);

        for (int i = 0; i < 4; i++) {
            int nx = k.x + dx[i];
            int ny = k.y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (ar[nx][ny] == 1) continue;
            if (visited[nx][ny]) continue;
            if (ar[nx][ny] == 2) {
                //비활성 바이러스 만났을 때
                if (find(tmp.begin(), tmp.end(), make_pair(nx, ny)) == tmp.end()) {
                    int is_fin = 1;
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            if (!visited[i][j] && !ar[i][j]) {
                                is_fin = 0;
                            }
                        }
                    }
                    if (is_fin) continue;
                } else {
                    continue;
                }
            }
            visited[nx][ny] = 1;
            q.push({nx, ny, k.time + 1});
        }  
    }

    //check
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j] && !ar[i][j]) {
                return;
            }
        }
    }

    answer = min(answer, time);
}

void get_combination(int st, int depth) {
    if (depth == m) {
        bfs();
        return;
    }

    for (int i = st + 1; i < v.size(); i++) {
        if (find(tmp.begin(), tmp.end(), v[i]) != tmp.end()) continue;
        tmp.push_back(v[i]);
        get_combination(i, depth + 1);
        tmp.pop_back();
    }
}

int main() {

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ar[i][j];
            if (ar[i][j] == 2) {
                v.push_back({i, j});
            }
        }
    }
    get_combination(-1, 0);
    
    if (answer == 1000000) cout << -1;
    else cout << answer;
    
    return 0;
}
