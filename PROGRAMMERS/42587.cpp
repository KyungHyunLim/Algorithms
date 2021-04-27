/*
프린터

우선 순위 프린터
*/

#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

bool printed[100];

int solution(vector<int> priorities, int location) {
    memset(printed, false, sizeof(printed));
    queue<pair<int,int>> q;
    for(int i=0; i<priorities.size(); i++){
        q.push(make_pair(i,priorities[i]));
    }
    
    int answer = 0;
    while(true){
        int idx = q.front().first;
        int p = q.front().second;
        q.pop();
        
        bool flag = true;
        // 우선순위 검사
        int _max = p;
        for(int i=0; i < priorities.size(); i++){
            if(printed[i]) continue;
            if(_max < priorities[i]){
                flag = false;
                break;
            }
        }
        
        // 우선순위가 더 큰게 없음
        if(flag){
            answer ++;
            printed[idx] = true;
            if(idx == location) return answer;
        }
        // 있음
        else{
            q.push(make_pair(idx, p));
        }          
    }
    return answer;
}
