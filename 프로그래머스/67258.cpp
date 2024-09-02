#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> solution(vector<string> gems) {
    
    vector<int> answer(2);
    set<string> s(gems.begin(), gems.end());
    map<string, int> m; 
    int length = gems.size()+1; 
    int i, start=0, end=0;
    
    while(1) {
        
        //끝나는 지점 구하기
        for (i = end; i < gems.size(); i++) {
            m[gems[i]]++;
            if (m.size() == s.size()) {
                end = i;
                break;
            }
        }
    
        if (i == gems.size())
            break;
    
        //시작지점 구하기
        for (i = start; i <=end; i++) {
            m[gems[i]]--;
            
            if (m[gems[i]] == 0) {
                start = i;
                m.erase(gems[i]);
                break;
            }
        }
        
        if (length > end-start) {
            answer[0] = start + 1;
            answer[1] = end + 1;
            length = end - start;
        }

        start++;
        end++;
    }
    
    return answer;
}