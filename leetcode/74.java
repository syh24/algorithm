class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        if (matrix[0][0] > target) return false;
        
        for (int[] row : matrix) {
            if (row[row.length - 1] < target) continue;
            if (row[0] > target) return false;

            Arrays.sort(row);
            int left = 0;
            int right = row.length - 1;

            while (left <= right) {
                int mid = (left + right) / 2;

                if (row[mid] == target) {
                    return true;
                } else if (row[mid] < target) {
                    left = mid + 1;
                } else if (row[mid] > target) {
                    right = mid - 1;
                }
            }
            break;
        }
        return false;
    }
}