#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, int> m;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer(2);
    int end_flag = 0;
    
    int s = 1;
    int turn = 1;
    char prev;
    
    for (int i = 0; i < words.size(); i++) {
        if (s > n) {
            s = 1;
            turn++;
        }
        
        m[words[i]]++;
        
        if (m[words[i]] > 1) {
            end_flag = 1;
            break;
        } else if (prev != NULL && prev != words[i][0]) {
            end_flag = 1;
            break;
        }
        
        prev = words[i][words[i].size() - 1];
        s += 1;
    }
    
    answer[0] = s;
    answer[1] = turn;
    
    
    if (!end_flag) {
        answer[0] = 0;
        answer[1] = 0;
    }
    

    return answer;
}