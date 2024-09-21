import java.util.*;

/*
카드 100장 -> 2~100사이의 수 고르고 그 이하 카드만 가지고 게임

상자 선택 -> 카드 번호 -> 상자 번호 -> 카드 번호 ...
*/


class Solution {
    
    int[] tmp;
    int[] global_cards;
    public int solution(int[] cards) {
        global_cards = cards;
        int answer = 0;
        
        for (int i = 0; i < cards.length; i++) {
            tmp = new int[cards.length + 1];
            tmp[i] = 1;
            int a = caculate(i);
            
            //첫 번째의 모든 상자 열었을 경우
            if (a == cards.length) {
                continue;
            }
            
            int b = 0;
            //두 번째 상자 열로 가자
            for (int j = 0; j < cards.length; j++) {
                if (tmp[j] == 1) continue;
                tmp[j] = 1;
                b = caculate(j);
                answer = Math.max(answer, a * b);
            }
        }
        
        return answer;
    }
    
    public int caculate(int cur) {
        int cnt = 1;
        int nx = cur;
        while (true) {
            nx = global_cards[nx];
            nx -= 1;
            //이미 열려있는 상자
            if (tmp[nx] == 1) {
                break;
            } else {
                cnt++;
                tmp[nx] = 1;
            }
        }
        
        return cnt;
    }
    
    
    
    
    
    
}