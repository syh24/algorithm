#include <bits/stdc++.h>

using namespace std;

int k, m;
int ar[6][6];
int visited[6][6];
queue<int> que;
int sum = 0;

struct acient {
    int ar[6][6];
    int rotate;
};

acient mp;

//회전 시킴
void doRotate(int sy, int sx, int cnt) {
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            mp.ar[i][j] = ar[i][j];
        }
    }
    for (int k=0; k < cnt; k++){
        // sy, sx를 좌측상단으로 하여 시계방향 90도 회전합니다.
        int tmp = mp.ar[sy+0][sx+2];
        mp.ar[sy+0][sx+2] = mp.ar[sy+0][sx+0];
        mp.ar[sy+0][sx+0] = mp.ar[sy+2][sx+0];
        mp.ar[sy+2][sx+0] = mp.ar[sy+2][sx+2];
        mp.ar[sy+2][sx+2] = tmp;
        tmp = mp.ar[sy+1][sx+2];
        mp.ar[sy+1][sx+2] = mp.ar[sy+0][sx+1];
        mp.ar[sy+0][sx+1] = mp.ar[sy+1][sx+0];
        mp.ar[sy+1][sx+0] = mp.ar[sy+2][sx+1];
        mp.ar[sy+2][sx+1] = tmp;
    }
    mp.rotate = cnt;
}

int doVisit() {
    int score = 0;
    for (int i=0;i<6;i++) {
        for (int j=0;j<6;j++) {
            visited[i][j] = false;
        }
    }

    int dy[4] = {0,1,0,-1}, dx[4] = {1,0,-1,0};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (!visited[i][j]) {
                queue<pair<int, int> > q, trace;
                q.push({i, j});
                trace.push({i, j});
                visited[i][j] = true;
                while (!q.empty()) {
                    pair<int,int> cur = q.front();
                    q.pop();
                    for (int k=0;k<4;k++){
                        int ny = cur.first+dy[k], nx=cur.second+dx[k];
                        if (0<=nx && nx<5 && 0<=ny && ny<5 && (mp.ar[ny][nx]==mp.ar[cur.first][cur.second]) && (!visited[ny][nx])) {
                            q.push({ny, nx});
                            trace.push({ny, nx});
                            visited[ny][nx] = true;
                        }
                    }
                }
                if (trace.size() >= 3) {
                    score += trace.size();
                    while (!trace.empty()) {
                        pair<int,int> t = trace.front(); trace.pop();
                        mp.ar[t.first][t.second] = 0;
                    }
                }
            
            }
        }
    }

    return score;
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> k >> m;


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> ar[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        que.push(t);
    }

    for (int i = 0; i < k; i++) {
        acient max_a;
        int max_score = 0;
        for (int k = 1; k <= 3; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    doRotate(j, i, k);
                    //탐사 진행
                    int score = doVisit();
                    if (max_score < score) {
                        max_score = score;
                        max_a = mp;
                    }
                }
            }
        }

        if (max_score == 0) { 
            break;
        }
    
        int ans = max_score;

        mp = max_a;

        while(1) {
            // 채워 넣기
            for (int i = 0; i < 5; i++) {
                for (int j = 4; j >= 0; j--) {
                    if (mp.ar[j][i] == 0) {
                        mp.ar[j][i] = que.front();
                        que.pop();
                    }
                }
            }
            max_score = doVisit();
            if (max_score == 0) break;
            ans += max_score;   
        }

        for (int i=0;i<5;i++){
            for (int j=0;j<5;j++) {
                ar[i][j] = mp.ar[i][j];
            }
        }
        cout << ans << " ";
    }

    return 0;
}