#include <string>
#include <vector>
#include <iostream>

using namespace std;

int arr[1001][1001];
int total = 0;

int check_pos(int dir, int h, int pos, int n) {
    if (dir == 0) {
        h += 1;
    } else if (dir == 1) {
        pos += 1;
    } else {
        h -= 1;
        pos -= 1;
    }
    
    if (h < 1 || h > n || pos >= h) return true;
    
    return arr[h][pos] != 0;
}

vector<int> solution(int n) {
    vector<int> answer;
    int h = 1;
    int pos = 0;
    int dir = 0;
    
    for (int i = 1; i <= n; i++) {
        total += i;
    }
    
    for (int i = 1; i <= total; i++) {
        arr[h][pos] = i;
        
        if(check_pos((dir % 3), h, pos, n)) dir++;
        
        int ndir = dir % 3;
        
        if (ndir == 0) {
            h += 1;
        } else if (ndir == 1) {
            pos += 1;
        } else {
            h -= 1;
            pos -= 1;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            answer.push_back(arr[i][j]);
        }
    }
    return answer;
}