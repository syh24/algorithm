#include <string>
#include <vector>
#include <iostream>

using namespace std;

int discount[4] = {10, 20, 30, 40};
int emoticon_length;
int max_users = -1;
int max_coin = -1;
vector<int> answer;

void dfs(vector<int> v, int depth, vector<vector<int>> u, vector<int> e) {
    if (depth == emoticon_length) {
        int contract_user = 0;
        int total_user_sum = 0;
        for (auto user : u) {
            float price_sum = 0;
            int per = user[0];
            int limit = user[1];
            
            for (int i = 0; i < emoticon_length; i++) {
                if (per > v[i]) continue;
                
                price_sum += ((e[i]/100) * (100 - v[i]));
            }

            if (limit <= price_sum) contract_user++;
            else total_user_sum += price_sum;
        }
        
        if (max_users < contract_user || (max_users == contract_user && max_coin <= total_user_sum)) {
            max_users = contract_user;
            max_coin = total_user_sum;
            answer.clear();
            answer.push_back(max_users);
            answer.push_back(max_coin);
        }
        
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        v.push_back(discount[i]);
        dfs(v, depth+1, u, e);
        v.pop_back();
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> dis_ratio;
    emoticon_length = emoticons.size();
    
    dfs(dis_ratio, 0, users, emoticons);
    
    return answer;
}