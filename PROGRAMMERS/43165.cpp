/*
타겟 넘버

기초적인 완전 탐색 문제 - dfs 활용

dfs(idx, sum)
- idx : 현재 선택 개수
- sum : 현재 까지 합
- idx가 N(숫자 개수)과 같으면,
  - sum과 T(target number)이 같으면 개수 증가
- + 선택하는 경우 dfs(idx+1, sum+ns[idx]);
- - 선택하는 경우 dfs(idx+1, sum-ns[idx]);
*/
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int answer;
int N, T;
vector<int> ns;
void dfs(int idx, int sum){
  // 다골랐으면
    if(idx == N){
      // 타겟넘버와 같으면, 개수증가
        if(sum == T) answer++;
        return;
    }
    dfs(idx+1, sum-ns[idx]); // - 선택
    dfs(idx+1, sum+ns[idx]); // + 선택
}

int solution(vector<int> numbers, int target) {
    answer = 0;
    ns = numbers;
    N = numbers.size();
    T = target;
    dfs(0, 0);
    return answer;
}
