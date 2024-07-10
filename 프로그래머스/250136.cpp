#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int n, m;
vector<vector<int>> _land;

struct la {
    //최소
    int mn;
    //최대
    int mx;
    //석유 크기
    int size;
};

la tmp;

vector<la> v;

void dfs(int x, int y) {

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (0 <= nx && nx < n && 0 <= ny && ny < m && _land[nx][ny] == 1) {
            _land[nx][ny] = -1;
            tmp.size += 1;
            tmp.mn = min(ny, tmp.mn);
            tmp.mx = max(tmp.mx, ny);
            dfs(nx, ny);
		}
	}
}

int solution(vector<vector<int>> land) {
    _land = land;
	n = land.size();
	m = land[0].size();
    
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (_land[i][j] == 1) {
                tmp.mn = j;
                tmp.mx = j;
				tmp.size = 1;
                _land[i][j] = -1;
                dfs(i, j);
				v.push_back(tmp);
            }
        }
    }
    
    int ans = -1;
    
    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (auto x : v) {
            if (x.mn <= i && i <= x.mx) {
               sum += x.size; 
            }
        }
        ans = max(ans, sum);
    }
    
    return ans;
}