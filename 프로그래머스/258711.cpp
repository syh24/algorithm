#include <bits/stdc++.h>

using namespace std;
/*
단반향 간선
도넛 모양: n개 정점, n개 간선
막대 모양: n개 정점, n-1개 간선
8자 모양: 2n+1개 정점, 2n+2개 간선

생성한 정점이 주어지고, 거기에 연결된 정점을 포함하는 그래프를 구하는 것
정점 번호, 도넛 수, 막대 수, 8자 수

*/

vector<vector<int>> v(1e6 + 1);

//in, out 간선 개수를 구함
unordered_map<int, int> in_map, out_map;

int center;
int dounut = 0, stick = 0, eight = 0;

void explore(int start) {
    
    queue<int> q;
    q.push(start);
    bool visited = false;

    while(!q.empty()) {
        int tmp = q.front();
        q.pop();
        
        //도넛인 경우
        if (tmp == start && visited) {
            dounut++;
            return;
        }
        
        //8자인 경우
        if (out_map[tmp] >= 2) {
            eight++;
            return;
        }
        
        for (int i = 0; i < v[tmp].size(); i++) {
            q.push(v[tmp][i]);
        }
        
        visited = true;
    }
    stick++;
}

vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer;
    
    int len = -1;
    
    for(auto x : edges) {
        len = max(len, max(x[0], x[1]));
        if (!out_map.count(x[0])) out_map[x[0]] = 0;
        if (!in_map.count(x[1])) in_map[x[1]] = 0;
        //벡터에 간선 정보 저장
        v[x[0]].push_back(x[1]);
        
        //간선 개수
        out_map[x[0]]++;
        in_map[x[1]]++;
    }
    
    vector<int> eight_dounut;
    
    for (int i = 1; i <= len; i++) {
        if (!in_map[i] && out_map[i] > 1) {
            center = i;
        }
    }
    
    for (int i = 0; i < v[center].size(); i++) {
        explore(v[center][i]);
    }
    
    answer.push_back(center);
    answer.push_back(dounut);
    answer.push_back(stick);
    answer.push_back(eight);
    
    return answer;
}