#include <string>
#include <vector>

using namespace std;

vector<vector<int>> ar;
vector<int> answer(2);

void recur(int s, int e, int size) {
    int same_flag = 1;
    int prev = -1;
    
    //모두 같은지 체크
    for (int i = s; i < s + size; i++) {
        for (int j = e; j < e + size; j++) {
            if (prev == -1) {
                prev = ar[i][j];
            } else {
                if (prev != ar[i][j]) {
                    same_flag = 0;
                    break;
                }
            }
        }
        if (!same_flag) break;
    }
    
    if (same_flag) {
        answer[prev]++;
    } else {
        int new_size = size / 2;
        recur(s, e, new_size);
        recur(s + new_size, e, new_size);
        recur(s, e + new_size, new_size);
        recur(s + new_size, e + new_size, new_size);
    }
    return;
}

vector<int> solution(vector<vector<int>> arr) {
    ar = arr;
    recur(0, 0, arr.size());
    return answer;
}