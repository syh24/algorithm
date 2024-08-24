#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 100000000;

unordered_map<int, int> gate, summit;

vector<vector<pii>> v(50505);

vector<int> ans;

void find(int n, vector<int> gates) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    vector<pii> tmp;
    vector<int> dist(n + 1, INF);
    vector<int> mx_value(n + 1, 0);
    //시작점 넣어주고 시작
    for (auto x : gates) {
        pq.push({0, x});
        dist[x] = 0;
    }
    
    
    while(!pq.empty()) {
        pii curr = pq.top();
        pq.pop();
        
        if (curr.first > dist[curr.second]) continue;
        
        if (summit[curr.second] == 1) {
            tmp.push_back(curr);
            continue;
        }
        
        for (auto next : v[curr.second]) {
            if (dist[next.first] > max(curr.first, next.second)) {
                dist[next.first] = max(curr.first, next.second);
                pq.push({dist[next.first], next.first});   
            }
        }
    }
    
    sort(tmp.begin(), tmp.end());
    ans.push_back(tmp[0].second);
    ans.push_back(tmp[0].first);
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    sort(summits.begin(), summits.end());
    //양방향 간선 세팅
    for (int i = 0; i < paths.size(); i++) {
        v[paths[i][0]].push_back({paths[i][1], paths[i][2]});
        v[paths[i][1]].push_back({paths[i][0], paths[i][2]});
    }
    
    //시작점 세팅
    for (int i = 0; i < gates.size(); i++) {
        gate[gates[i]] = 1;
    }
    
    //산봉우리 세팅
    for (int i = 0; i < summits.size(); i++) {
        summit[summits[i]] = 1;
    }
    
    find(n, gates);
    
    return ans;
}