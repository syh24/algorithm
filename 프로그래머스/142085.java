import java.util.*;

class Solution {
    public int solution(int n, int k, int[] enemy) {
        int answer = 0;
        
        Queue<Integer> q = new PriorityQueue<>();
        int idx = 0;
        
        if (k >= enemy.length) return enemy.length;
        
        for (idx = 0; idx < k; idx++) {
            q.add(enemy[idx]);
        }
        int cur;
        
        while (idx < enemy.length) {
            cur = enemy[idx];
            if (q.peek() < enemy[idx]) {
                cur = q.poll();
                q.add(enemy[idx]);
            }
            
            if (n >= cur) {
                n -= cur;
            } else break;
            
            idx++;
        }
        
        return idx;
    }
}