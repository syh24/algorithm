import java.util.*;

class Solution {
    int n, m;
    int[] st = new int[2];
    int[] ex = new int[2];
    int[] lv = new int[2];
    int[] dx = {1, -1, 0, 0};
    int[] dy = {0, 0, -1, 1};
    String[] g_maps;
    boolean[][] visited;
    
    public int bfs(int[] start, int[] end) {
        Queue<int[]> q = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            Arrays.fill(visited[i], false);
        }
        visited[start[0]][start[1]] = true;
        
        q.add(new int[]{start[0], start[1], 0});
        
        while(!q.isEmpty()) {
            int[] cur = q.poll();
            
            if (cur[0] == end[0] && cur[1] == end[1]) {
                return cur[2];
            }
            
            for (int i = 0; i < 4; i++) {
                int nx = cur[0] + dx[i];
                int ny = cur[1] + dy[i];
                
                if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                    if (g_maps[nx].charAt(ny) != 'X' && visited[nx][ny] == false) {
                        visited[nx][ny] = true;
                        q.add(new int[]{nx, ny, cur[2] + 1});
                    }
                }
            }
        }
        return -1;
    }
    
    public int solution(String[] maps) {
        int answer = 0;
        n = maps.length;
        m = maps[0].length();
        g_maps = maps;
        visited = new boolean[n + 1][m + 1];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maps[i].charAt(j) == 'S') {
                    st[0] = i;
                    st[1] = j;
                } else if (maps[i].charAt(j) == 'L') {
                    lv[0] = i;
                    lv[1] = j;
                } else if (maps[i].charAt(j) == 'E') {
                    ex[0] = i;
                    ex[1] = j;
                }   
            }
        }
        int k;
        k = bfs(st, lv);
        if (k == -1) return -1;
        answer += k;
        
        k = bfs(lv, ex);
        if (k == -1) return -1;
        answer += k;
        
        return answer;
    }
}