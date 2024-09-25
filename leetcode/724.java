class Solution {
    public int pivotIndex(int[] nums) {
        int[] prefix = new int[nums.length+1];
        prefix[0] = 0;
        for (int i = 1; i <= nums.length; i++) {
            prefix[i] = prefix[i-1] + nums[i-1];
        }

        int idx = 1;
        int leftSum = 0;
        int rightSum = 1;
        while(true) {
            if (idx > nums.length) break;
            leftSum = prefix[idx-1] - prefix[0];
            rightSum = prefix[nums.length] - prefix[idx];

            if (leftSum == rightSum) return idx-1;

            idx++;
        }

        return -1;
    }
}