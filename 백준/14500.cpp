#include <bits/stdc++.h>

using namespace std;

int n, m;
int ar[510][510];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int visited[510][510];
int answer = -1;

void dfs(int x, int y, int depth, int sum) {

    if (depth == 3) {
        answer = max(answer, sum);
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (visited[nx][ny]) continue;
        if (depth == 1) {
            visited[nx][ny] = 1;
            dfs(x, y, depth + 1, sum + ar[nx][ny]);
            visited[nx][ny] = 0;
        }
        visited[nx][ny] = 1;
        dfs(nx, ny, depth + 1, sum + ar[nx][ny]);
        visited[nx][ny] = 0;

    }

}


int main() {
   
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> ar[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = 1;
            dfs(i, j, 0, ar[i][j]);
            visited[i][j] = 0;
        }
    }

    cout << answer;


    return 0;
}