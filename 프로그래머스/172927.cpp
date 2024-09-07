#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

unordered_map<string, int> m;

struct tmp {
    int depth;
    vector<int> v;
    int cost;
};

int solution(vector<int> picks, vector<string> minerals) {
    int answer = 1000000;
    m["diamond"] = 0;
    m["iron"] = 1;
    m["stone"] = 2;
    queue<tmp> q;
    q.push({0, picks, 0});
    int sd = (picks[0] + picks[1] + picks[2]) * 5;
    int len = minerals.size();
    int ky = min(sd, len);
    
    cout << ky <<" ";
    
    while(!q.empty()) {
        auto x = q.front();
        q.pop();
        
        if (x.depth >= ky) {
            answer = min(x.cost, answer);
            break;
        }
        
        for (int i = 0; i < 3; i++) {
            if (x.v[i] <= 0) continue;
            vector<int> tmp = x.v;
            int cost = x.cost;
            
            for (int j = x.depth; j < x.depth + 5; j++) {
                if (j >= ky) break;
                if (m[minerals[j]] - i >= 0) {
                    cost += 1;
                } else if (m[minerals[j]] - i == -1) {
                    cost += 5;
                } else {
                    cost += 25;
                }
            }
            
            tmp[i]--;
            q.push({x.depth+5, tmp, cost});
        }
    }
    
    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        answer = min(answer, x.cost);
    }
    

    
    return answer;
}