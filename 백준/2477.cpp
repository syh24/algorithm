#include <iostream>
#include <vector>

using namespace std;

int k;
vector<pair<int, int>> v,temp;

int ar[10];

int main() {
    cin >> k;

    for (int i = 0; i < 6; i++) {
        int a, b; cin >> a >> b;
        v.push_back({a, b});
        ar[a]++;
    }

    int row, col, tmp_row, tmp_col, pos;
    int cnt = 0;
    for (int i = 0; i < (v.size() * 2); i++) {
        int p = i % v.size();
        if (ar[v[p].first] == 1) {
            cnt++;
            if (cnt == 2) {
                pos = p;
            }
            if (v[p].first <= 2) {
                col = v[p].second;
            } else {
                row = v[p].second;
            }
        } else {
            cnt = 0;
        }
    }

    cout << ((row * col) - (v[(pos+2)%6].second * v[(pos+3)%6].second)) * k;
    
    return 0;
}
