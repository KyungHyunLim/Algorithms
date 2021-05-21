/*
약수의 개수와 덧샘
*/
#include <string>
#include <vector>

using namespace std;

// 약수의 개수 구하기
int check(int num){
  // 1이면 1개
    if(num == 1) return 1;
  // 2부터는 1과 자기 자신을 기본적으로 포함
    int count = 2;
  // 2 ~ num/2 까지 약수 개수 검사
    for(int i = 2; i<=num/2; i++){
        if(num % i == 0) count++;
    }
    return count;
}


int solution(int left, int right) {
    int answer = 0;
    
  // left ~ right 까지
    for(int i=left; i<=right; i++){
      // 약수의 개수가 짝수면 더하기
        if(check(i) % 2 == 0) answer += i;
      // 홀수면 빼기
        else answer -= i;
    }
    
    return answer;
}
