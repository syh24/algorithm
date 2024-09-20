/*
1. 가고싶은 편의점으로 4가지 방향으로 한칸 이동
2. 편의점에 도착하면 이제 해당칸 편의점 지나갈 수 없음.
3. t <= m을 만족한다면 가장 가까이 있는 베이스캠프로 들어감. 
*/

import java.io.*;
import java.util.*;

public class Main {
    static int t = 1;
    static int n, m;
    static int count = 0;
    static int[][] grid;
    static int[][] base;
    static int[][] pp;
    static int[] solve = new int[40];
    static int[] dx = {-1, 0, 0, 1};
    static int[] dy = {0, -1, 1, 0};
    static int[] next_move = new int[2];

    public static void main(String[] args) throws IOException {
        // 여기에 코드를 작성해주세요.
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] first_line = br.readLine().split(" ");
        n = Integer.parseInt(first_line[0]);
        m = Integer.parseInt(first_line[1]);
        grid = new int[n+5][n+5];
        base = new int[m+5][2];
        pp = new int[m+5][2];

        for (int i = 0; i < n; i++) {
            String[] line = br.readLine().split(" ");
            for (int j = 0; j < n; j++) {
                grid[i][j] = Integer.parseInt(line[j]);
            }
        }

        for (int i = 1; i <= m; i++) {
            String[] line = br.readLine().split(" ");
            base[i][0] = Integer.parseInt(line[0]) - 1;
            base[i][1] = Integer.parseInt(line[1]) - 1;
        }

        while (true) {
            if (t > 1) {
                action1();
                action2();
            }
            if (t <= m) {
                action3();
            }
            if (count == m) break;
            //시간 증가
            t += 1;
        }

        System.out.println(t);
    }

    public static void action1() {
        int len = t > m ? m + 1 : t;
        for (int i = 1; i < len; i++) {
            if (solve[i] == 1) continue;
            bfs2(pp[i][0], pp[i][1], i);
        }
    }

    public static void action2() {
        int len = t > m ? m + 1 : t;

        for (int i = 1; i < len; i++) {
            if (solve[i] == 1) continue;
            //편의점 도착한 지 체크
            if (base[i][0] == pp[i][0] && base[i][1] == pp[i][1]) {
                grid[base[i][0]][base[i][1]] = 2;
                solve[i] = 1;
                count += 1;
            }
        }

        return;
    }

    public static void action3() {
        bfs(t);
        grid[pp[t][0]][pp[t][1]] = 2;
    }

    public static void bfs(int time) {
        int[] start = base[time];
        Queue<int[]> q = new LinkedList<>();
        boolean[][] visited = new boolean[16][16];
        q.add(new int[]{start[0], start[1], 0});
        visited[start[0]][start[1]] = true;
        int[] tmp = {100, 100};
        int small = -1;

        while (!q.isEmpty()) {
            int[] cur = q.poll();

            if ((small == -1 && grid[cur[0]][cur[1]] == 1) || (cur[2] == small)) {
                small = cur[2];
                if (tmp[0] > cur[0]) {
                    tmp[0] = cur[0];
                    tmp[1] = cur[1];
                } else if (tmp [0] == cur[0] && tmp[1] > cur[1]) {
                    tmp[0] = cur[0];
                    tmp[1] = cur[1];
                }
                continue;
            }

            for (int i = 0; i < 4; i++) {
                int tx = cur[0] + dx[i];
                int ty = cur[1] + dy[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
                if (grid[tx][ty] == 2 || visited[tx][ty]) continue;
                visited[tx][ty] = true;
                q.add(new int[]{tx ,ty, cur[2] + 1});
            }
        }
        pp[time] = tmp;
    }

    public static void bfs2(int a, int b, int k) {
        Queue<int[]> q = new LinkedList<>();
        boolean[][] visited = new boolean[16][16];
        q.add(new int[]{a, b, -1, -1});

        while (!q.isEmpty()) {
            int[] cur = q.poll();

            if (cur[0] == base[k][0] && cur[1] == base[k][1]) {
                pp[k][0] = cur[2];
                pp[k][1] = cur[3];
                return;
            }

            for (int i = 0; i < 4; i++) {
                int tx = cur[0] + dx[i];
                int ty = cur[1] + dy[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
                if (grid[tx][ty] == 2 || visited[tx][ty]) continue;
                visited[tx][ty] = true;
                if (cur[2] == -1 && cur[3] == -1) {
                    q.add(new int[]{tx ,ty, tx, ty});    
                }
                q.add(new int[]{tx ,ty, cur[2], cur[3]});
            }
        }
    }
}