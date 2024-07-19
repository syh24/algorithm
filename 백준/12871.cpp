#include <bits/stdc++.h>

using namespace std;


int main() {
   
    string s, t, a, b;
    cin >> s >> t;

    if (s.length() <= t.length()) {
        a = t;
        b = s;
    }
    else {
        a = s;
        b = t;
    }
    int al = a.length();
    int bl = b.length();
    int len = al * bl;

    string tmp1 = "";
    string tmp2 = "";

    for (int i = 0; i < len; i++) {
        int j = i % al;
        tmp1 += a[j];
    }

    for (int i = 0; i < len; i++) {
        int j = i % bl;
        tmp2 += b[j];
    }

    if (tmp1 == tmp2) cout << 1;
    else cout << 0;
    

    return 0;
}