#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> v;
int main() {

    int n; cin >> n;

    if (n == 0){
        cout << 0 << "\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        v.push_back(a);
    }

    int k = round(n * 0.15);

    sort(v.begin(), v.end());

    int sum = 0;

    for (int i = k; i < n - k; i++) {
        sum += v[i];
    }

    cout << round((double) sum / (n - (2*k)));
    
    return 0;
}
