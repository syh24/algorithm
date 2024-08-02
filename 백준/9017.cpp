#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        int arr[1005], fifth[205];
        int team[205] = {}, tot[205] = {}, cnt[205] = {};
        for(int i=0 ; i<n ; i++) {
            cin >> arr[i];
            team[arr[i]]++;
        }
        int score = 1;
        for(int i=0 ; i<n ; i++) {
            if(team[arr[i]] == 6) {
                if(cnt[arr[i]] < 4) tot[arr[i]] += score;
                else if(cnt[arr[i]] == 4) fifth[arr[i]] = score;
                cnt[arr[i]]++;
                score++;
            }
        }
        int mn = 1e6;
        int mn_num = 0;
        for(int i=1 ; i<=200 ; i++) {
            if(tot[i]) {
                if(tot[i] == mn && fifth[i] < fifth[mn_num]) {
                    mn = tot[i];
                    mn_num = i;
                }
                else if(tot[i] < mn) {
                    mn = tot[i];
                    mn_num = i;
                }
            }
        }
        cout << mn_num << '\n';
    }
}