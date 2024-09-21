class Solution {
    public boolean wordBreak(String s, List<String> wordDict) {
        boolean[] dp = new boolean[s.length() + 1];
        dp[0] = true;

        //문제 아이디어
        // 기존 string을 회손하지 않고, substring으로 비교
        // memorization기법 사용
        for (int i = 1; i <= s.length(); i++) {
            for (String w : wordDict) {
                int idx = i - w.length();
                if (idx >= 0 && dp[idx] && s.substring(idx, i).equals(w)) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.length()];
    }
}