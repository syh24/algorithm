#include <string>
#include <vector>

using namespace std;

int arr[1000001];

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    
    int size = 10000000;
    
    
    for (int i = 0; i < sequence.size(); i++) {
        arr[i+1] = arr[i] + sequence[i];
    }
    
    int a = 0, b = 0;
    
    //presum + sliding window
    while (1) {
        int sum = arr[b] - arr[a];
        if (sum < k) {
            if (b == sequence.size()) break;
            b++;
        } else if (sum == k) {
            if (size > b - a + 1) {
                size = b - a + 1;
                answer.clear();
                answer.push_back(a);
                answer.push_back(b-1);
            }
            if (b != sequence.size()) {
                b++;
            } else {
                a++;
            }
        } else {
            a++;
        }
    }
    
    return answer;
}