class Solution {
    public int solution(String[] board) {
        int answer = -1;
        int ocnt = 0;
        int xcnt = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i].charAt(j) == 'O') {
                    ocnt++;
                } else if (board[i].charAt(j) == 'X') {
                    xcnt++;
                }
            }
        }
        
        if (xcnt > ocnt) return 0;
        //이제 3이상인거 체크
        if (ocnt - xcnt <= 1) {
            if (checkFinish(board, 'O') && checkFinish(board, 'X')) {
                return 0;
            } else if(checkFinish(board, 'O')) { 
                if (ocnt == xcnt) return 0;
            }else if (checkFinish(board, 'X')) {
                if (ocnt != xcnt) return 0;
            }
            
            return 1;
        } else {
            return 0;
        }
    }
    
    public boolean checkFinish(String[] board, char c) {
        if (board[0].charAt(0) == c && board[1].charAt(1) == c && board[2].charAt(2) == c) return true;
        
        if (board[0].charAt(2) == c && board[1].charAt(1) == c && board[2].charAt(0) == c) return true;
        
        for (int i = 0; i < 3; i++) {
            boolean flag1 = true;
            boolean flag2 = true;
                
            for (int j = 0; j < 3; j++) {
                if (board[i].charAt(j) != c) {
                    flag1 = false;
                }
                
                if (board[j].charAt(i) != c) {
                    flag2 = false;
                }
            }
            
            if (flag1 || flag2) return true;
        }
        
        return false;
    }
}