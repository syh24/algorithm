#include <bits/stdc++.h>

using namespace std;

string answer = "";
string tmp = "";
int dy[4] = { 0, -1, 1, 0 };
int dx[4] = { 1, 0, 0, -1 };

string alpha = "dlru";

int gn, gm, gr, gc, gk, l;

void dfs(int x, int y, int depth) {
    if (answer.length() != 0) return;
    
    if (depth == gk) {
        if (x == gr && y == gc) {
            if (answer.length() == 0) {
                answer = tmp;
            }
        }
        return;
    }
    
    //현재 위치에서 탈출경로까지 거리랑 K 비교
    if(abs(gr - x) + abs(gc - y) + depth > gk){
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (0 < nx && nx <= gn && 0 < ny && ny <= gm) {
            tmp += alpha[i];
            dfs(nx, ny, depth + 1);
            if (answer.length() != 0) return;
            tmp.pop_back();
        }
    }
    
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    
    int dist = abs(x - r) + abs(y - c);
    l = k - dist;
    if (l < 0 || l % 2 != 0) {
        return "impossible";
    }
    
    gn = n; gm = m; gr = r; gc = c; gk = k;
    dfs(x, y, 0);
    
    return answer == "" ? "impossible" : answer;
}