#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dice_g;
vector<int> a, b, a_sum, b_sum;
int check[11];
int n;

int win_rate = -1;
vector<int> ans;

void calScore(int x,int sumA, int sumB) {
    if (x == a.size()) {
        a_sum.push_back(sumA);
        b_sum.push_back(sumB);
        return;
    }

    for (int i = 0; i < 6; i++) {
        calScore(x + 1, sumA + dice_g[a[x]][i], sumB + dice_g[b[x]][i]);
    }
}

void combination(int x, int depth) {

    if (depth == n / 2) {
        //a, b 백터에 각각 조합 주사위 인덱스 저장
        for (int i = 0; i < n; i++) {
            if (check[i]) b.push_back(i);
            else a.push_back(i);
        }

        // 점수의 합 구성 a_sum, b_sum
        calScore(0, 0, 0);

        //정렬
        sort(a_sum.begin(), a_sum.end());
        sort(b_sum.begin(), b_sum.end());
        
        //승, 패 계산
        int win = 0, lose = 0;
        for (int k : a_sum) {
            int pos1 = lower_bound(b_sum.begin(), b_sum.end(), k) - b_sum.begin();
            win += pos1;
        }

        //최댓값 갱신
        if (win_rate < win) {
            win_rate = win;
            ans.clear();
            for (int i = 0; i < a.size(); i++) {
                ans.push_back(a[i] + 1);
            }
        }

        //초기화
        a.clear();
        b.clear();
        a_sum.clear();
        b_sum.clear();
        
        return;
    }

    for (int i = x + 1; i < n; i++) {
        check[i] = 1;
        combination(i, depth + 1);
        check[i] = 0;
    }
}


vector<int> solution(vector<vector<int>> dice) {
    dice_g = dice;
    n = dice.size();
    //조합으로 어떤 주사위 굴릴 지 선택 a, b
    //점수의 합 구함 -> a, b 각각 vector에 저장
    //b vector 순회하면서 lower_bound, upper_bound a vector 승 / 패 합산
    // 확률 갱신해주면서 가장 확률 높은 조합 return


    for (int i = 0; i < n; i++) {
        check[i] = 1;
        combination(i, 1);
        check[i] = 0;
    }
    return ans;
}