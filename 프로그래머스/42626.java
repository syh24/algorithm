import java.util.*;

class Solution {
    public int solution(int[] scoville, int k) {
        int answer = 0;
        Queue<Long> q = new PriorityQueue<>();
        
        for (int sc: scoville) {
            q.add((long) sc);
        }
        boolean f = false;
        while (q.size() > 1) {
            long a = q.poll();
            if (a >= k) {
                f = true;
                break;
            }
            long b = q.poll();
            long c = a + b * 2;
            q.add(c);
            answer++;
        }
        
        if (q.poll() >= k) f = true;
        
        return f ? answer : -1;
    }
}