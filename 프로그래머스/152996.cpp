#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(vector<int> w) {
    long long answer = 0;

    sort(w.begin(), w.end());
    
    for(int i = 0; i < w.size() - 1; i++) {
        for (int j = i + 1; j < w.size(); j++) {
            int a = w[j];
            int b = w[i];

            if (a == b) {
                answer++;
                continue;
            }

            if (a == 2 * b) {
                answer++;
                continue;
            }

            if (a * 2 == 3 * b) {
                answer++;
                continue;
            }
            
            if (a * 3 == 4 * b) {
                answer++;
                continue;
            }

        }
    }
    
    return answer;
}