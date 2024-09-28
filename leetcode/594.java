class Solution {
    public int findLHS(int[] nums) {
        Arrays.sort(nums);
        int ans = 0;

        int mn = nums[0];
        for (int i = 0; i < nums.length; i++) {
            int cnt = 0;
            int k = i;
            boolean f = false;
            while (k < nums.length) {
                if (Math.abs(nums[k] - nums[i]) <= 1) {
                    cnt++;
                    if (Math.abs(nums[k] - nums[i]) == 1) f = true;
                } else {
                    break;
                }
                k++;
            }
            if (f)
                ans = Math.max(cnt, ans);
        }    

        return ans;
    }
}