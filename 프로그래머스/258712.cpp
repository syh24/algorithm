#include <bits/stdc++.h>

using namespace std;

/*
선물 비교값이 두개 있음
주고받은 수, 선물 지수
주고받은 수 -> 선물 지수 -> 거래 x
둘 다 같으면 -> 선물을 주고받지 않음
*/

unordered_map<string, int> give, take, answer;
unordered_map<string, unordered_map<string, int>> trade;

vector<string> split(string str) {
    vector<string> tmp;
    int i;
    for (i = 0; i < str.size(); i++) {
        if (str[i] == ' ') break;
    }
    
    tmp.push_back(str.substr(0, i));
    tmp.push_back(str.substr(i+1, str.size()));
    
    return tmp;
}

int solution(vector<string> friends, vector<string> gifts) {
    //초기화
    for (auto x : friends) {
        give[x] = 0;
        take[x] = 0;
        answer[x] = 0;
        for (auto k : friends) {
            trade[x][k] = 0;
        }
    }
    
    for (auto x : gifts) {
        vector<string> tmp = split(x);
        give[tmp[0]] += 1;
        take[tmp[1]] += 1;
        trade[tmp[0]][tmp[1]] += 1;
    }
    
    //선물 체크
    for (int i = 0; i < friends.size() - 1; i++) {
        for (int j = i + 1; j < friends.size(); j++) {
            int itoj = trade[friends[i]][friends[j]];
            int jtoi = trade[friends[j]][friends[i]];
            if (itoj < jtoi) {
                answer[friends[j]] += 1;
            } else if (itoj > jtoi) {
                answer[friends[i]] += 1;
            } else {
                //같은 경우 선물 지수 비교
                if (itoj == 0 && jtoi && 0) {
                    continue;
                } else {
                    int giftI = give[friends[i]] - take[friends[i]];
                    int giftJ = give[friends[j]] - take[friends[j]];
                    if (giftI > giftJ) {
                        answer[friends[i]] += 1;
                    } else if (giftI < giftJ) {
                        answer[friends[j]] += 1;
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    
    int max_gift = -1;
    
    for (auto x : friends) {
        max_gift = max(max_gift, answer[x]);     
    }
    
    return max_gift;
}