class Solution {
    public int integerReplacement(long n) {
        int ans = 0;

        while (n != 1) {
            if (n % 2 == 0) {
                n /= 2;
            } else {
                if ( (n + 1) % 4 == 0 && (n - 1 != 2) ) n++;
                else n--;
            }
            ans++;
        }

        return ans;
    }
}