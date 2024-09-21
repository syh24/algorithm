class Solution {

    public int uniquePaths(int m, int n) {
        int[] dp_row = new int[n+1];
        Arrays.fill(dp_row, 1);

        for (int i = 1; i < m; i++) {
            int[] tmp = new int[n+1];
            Arrays.fill(tmp, 1);
            for (int j = 1; j < n; j++) {
                tmp[j] = tmp[j-1] + dp_row[j];
            }
            dp_row = tmp;
        }

        return dp_row[n-1];
    }
}