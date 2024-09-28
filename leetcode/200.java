class Solution {
    int ans = 0;
    int[] dx = {0, 1, -1, 0};
    int[] dy = {-1, 0, 0, 1};
    int n,m;
    boolean[][] visited;


    public int numIslands(char[][] grid) {
        visited = new boolean[301][301];

        n = grid.length;
        m = grid[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '0') continue;
                if (visited[i][j]) continue;
                Queue<int[]> q = new LinkedList<>();
                q.add(new int[]{i, j});
                visited[i][j] = true;
                while (!q.isEmpty()) {
                    int[] cur = q.poll();

                    for (int l = 0; l < 4; l++) {
                        int nx = cur[0] + dx[l];
                        int ny = cur[1] + dy[l];
                        if (nx < 0 || nx >= n || ny < 0 || ny >=m) continue;
                        if (grid[nx][ny] == '0' || visited[nx][ny]) continue;
                        visited[nx][ny] = true;
                        q.add(new int[]{nx, ny});
                    }
                }
                ans++;
            }
        }

        return ans;
    }
}