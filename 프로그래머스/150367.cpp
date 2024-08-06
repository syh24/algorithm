#include <bits/stdc++.h>

using namespace std;

/*
1. 십진수로 숫자가 주어진다.
2. 이진수로 변환
3. 이진트리로 해당 수를 표현할 수 있는지 체크
pre order 방식으로 트리 순회

key point: 부모 노드가 0이면 자식 노드가 존재할 수 없다!

*/

string binary_str = "";
int flag = 1;

void explore_left_child(long long root, long long q);

void explore_right_child(long long root, long long q);

//십진수 -> 이진수 변환
void toBinary(long long n) {
    if (n != 0) {
        toBinary(n / 2);
    }
    binary_str += to_string(n % 2);
}

void length_check() {
    int len = binary_str.size();
    int pos = 0;
    for (int i = 0; i < binary_str.size(); i++) {
        if (binary_str[i] == '1') break;
        pos++;
        len--;
    }
    
    string tmp = binary_str.substr(pos);
    int k;
    int i = 1;
    while(true) {
        k = pow(2, i) - 1;
        if (k >= len) break;
        i++;
    }
    
    string tmp2 = "";
    for (int i = 0; i < k - len; i++) {
        tmp2 += '0';
    }
    
    binary_str = tmp2 + tmp;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    
    for(auto x : numbers) {
        flag = 1;
        binary_str = "";
        toBinary(x);
        length_check();
        
        //루트 노드는 항상 가운데
        int root = binary_str.size() / 2;
        
        //좌우 자식 노드들 탐색하면서 이진트리를 만족하는지 탐색
        explore_left_child(root, (root + 1)/2);
        explore_right_child(root, (root + 1)/2);
        
        answer.push_back(flag);
    }
    
    return answer;
}

void explore_left_child(long long root, long long q) {
    if (!flag) return;
    if (root <= 0 || q == 0) return;
    if (binary_str[root] == '0' && binary_str[root - q] == '1') {
        flag = 0;
        return;
    }
    
    explore_left_child(root - q, q / 2);
    if (!flag) return;
    explore_right_child(root - q, q / 2);
}

void explore_right_child(long long root, long long q) {
    if (!flag) return;
    if (q == 0 || root <= 0 || root >= binary_str.size()) return;
    if (binary_str[root] == '0' && binary_str[root + q] == '1') {
        flag = 0;
        return;
    }
    
    explore_left_child(root + q, q / 2);
    if (!flag) return;
    explore_right_child(root + q, q / 2);
}