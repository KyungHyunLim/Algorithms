/*
구명보트 (그리디)

- 정렬 후, 가장 무거운 사람과 가장 가벼운 사람 짝지어 보기.
=> 가장 무거운 사람들 최소횟수로 내보낼수 있는 방법은 가장 가벼운 사람과 짝을지어 2명을 만드는것.


*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 구명보트 -> 한번에 최대 2명씩 밖에 탈 수 없음, 무게 제한 존재
// 구명 보트를 최대한 적게 사용하여 모든 사람을 구출
// 사람을 구출할 수 없는 경우는 없음, 무게 제한 > 사람 몸무게 최대값

bool rescued[50000];

int solution(vector<int> people, int limit) {
    sort(people.begin(), people.end());
    int cnt = 0;
    int size = people.size();
    int cur = people.size() - 1;
    int used = 0;
    int idx = 0;
    while(idx <= cur){
        // 현재 사람과 아직 구출되지 않은 가장 작은 사람의 합이
        // 무게 제한을 넘지 않으면
        if(people[cur] + people[idx] <= limit){
            rescued[cur] = true;
            rescued[idx] = true;
            idx++;
            // 두명 동시에 구출
            cnt += 2;
            cur--;
        }
        // 무게 제한을 넘으면 현재 사람만 구출
        else{
            rescued[cur] = true;
            cur--;
        }
        // 사용 횟수 증가
        used++;
        
    }
    
    return used;
}
