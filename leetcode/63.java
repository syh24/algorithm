class Solution {
    public int uniquePathsWithObstacles(int[][] obstacleGrid) {
        int m = obstacleGrid.length;
        int n = obstacleGrid[0].length;
        int[][] dp_row = new int[m+1][n+1];
        boolean zero_flag = false;

        if(obstacleGrid[0][0] == 1) return 0;

        for (int i = 0; i < n; i++) {
            if (obstacleGrid[0][i] == 1) zero_flag = true;
            if (!zero_flag) dp_row[0][i] = 1;
            else {
                dp_row[0][i] = 0;
            }
        }

        zero_flag = false;
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[i][0] == 1) zero_flag = true;
            if (!zero_flag) dp_row[i][0] = 1;
            else {
                dp_row[i][0] = 0;
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) continue;
                dp_row[i][j] = dp_row[i][j-1] + dp_row[i-1][j];
            }
        }

        return dp_row[m-1][n-1];
    }
}