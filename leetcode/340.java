class Solution {
    int[] ar = new int[300];
    public int lengthOfLongestSubstringKDistinct(String s, int k) {
        Set<Character> set = new HashSet<>();
        Arrays.fill(ar, 0);
        int ans = 0;

        int left = 0, right = 0;
        while(left <= right) {
            if (set.size() > k) {
                ans = Math.max(right-left-1, ans);
                while (left < right) {
                    char tmp = s.charAt(left);
                    ar[tmp] -= 1;
                    if (ar[tmp] == 0) {
                        set.remove(tmp);
                        left++;
                        break;
                    }
                    left++;
                }
            } else {
                if (right >= s.length()) break;
                set.add(s.charAt(right));
                ar[s.charAt(right)] += 1;
                right++;
            }
        }

        if (set.size() == k) {
            ans = Math.max(right - left, ans);
        }

        if (k == 0) return 0;
        return ans == 0 ? s.length() : ans;
    }
}