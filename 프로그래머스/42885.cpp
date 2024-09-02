#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int ar[50001];

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end());
    
    
    int s = 0, e = people.size() - 1;
    
    while(s<e) {
        while (1) {
            if (people[s] + people[e] <= limit) break;
            e--;
        }        
        
        ar[s] = 1;
        ar[e] = 1;
        answer++;
        s++;
        e--;
    }
    
    for (int i = 0; i < people.size(); i++) {
        if (!ar[i]) answer++;
    }
    
    return answer;
}