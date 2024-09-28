class Solution {
    public long solution(int cap, int n, int[] deliveries, int[] pickups) {
        long answer = 0;
        int pos = n-1;
        int dv = cap;
        int pk = cap;
        while (pos >= 0 && deliveries[pos] == 0 && pickups[pos] == 0) pos--;
        answer += (pos+1) * 2;
        while (true) {
            if (pos < 0) break;

            dv = dv - deliveries[pos];
            pk = pk - pickups[pos];

            int cnt = 0;
            while(dv < 0 || pk < 0) { 
                dv += cap;
                pk += cap;
                cnt++;
            }
            answer += (pos+1) * 2 * cnt;

            pos--;
        }
        
        
        return answer;
    }
}