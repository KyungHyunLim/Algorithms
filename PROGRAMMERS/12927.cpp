/*
야근 지수
-> 아래 주석 참조
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;
/*
    야근지수가 제곱을 하기 때문에 최대 값에서 -1을 해주는 것이 항상 최소값을 가진다.
    a, b, c, ... 가 있을 때
    a > b > c , ... 라고 가정하면
    n = 0일때 야근지수는 a^2 + b^2 + c^2 + ... (A라 하자)이다.
    야근 지수를 최대값에서 뺏을 때와 그 이전에서 뺏을 때를 비교 해보면 
    
    * 0. a^2 + b^2 + c^2 + ... => A
    1. (a-1)^2 + b^2 + c^2 + ...
    2. a^2 + b^2 + (c-1)^2 + ...
    
    식 1. => A + -2a + 1
    식 2. => A + -2c + 1
    로 변환할 수 있다.
    
    여기서 a > c이고 정수 임으로 
    => -2a < -2c
    => -2a + 1 < -2c + 1
    => A -2a + 1 < A - 2c + 1
    => 식 1은 식 2보다 항상 작다.
    
    항상 최대값을 갱신하기 위해 우선순위 큐를 활용한다.
*/
long long solution(int n, vector<int> works) {   
    priority_queue<int> pq(works.begin(), works.end());
    while(n > 0){
        if(pq.top() > 0){
            int temp = pq.top();
            pq.pop();
            pq.push(temp-1);
            n--;
        }
        else{
            break;
        }
    }
    long long answer = 0;
    while(!pq.empty()){
        long long temp = pq.top();
        pq.pop();
        answer += (temp*temp);
    }  
    return answer;
}
