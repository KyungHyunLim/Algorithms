/*
다음 큰 숫자

1. n보다 큰 자연수
2. 이진수 변환시 n과 1의 갯수가 같음

*/

#include <string>
#include <vector>

using namespace std;

// 1의 개수 파악
int amount_of_one(int n){
    int cnt = 0;
    int num = 1;
    // 2진수 변환시 몇자리인지 확인
    while(num < n){
        num *= 2;
        cnt++;
    }
    
    // 1 시프트 시키며 and 연산으로 1의 개수 확인
    int count = 0;
    for(int i=0; i<=cnt; i++){
        if(n & (1<<i)) count++;
    }
    // 1의 개수 반환
    return count;
}

int solution(int n) {
    // n의 1의 개수
    int n_1 = amount_of_one(n);
    for(int i=n+1; ;i++){
        // 1의 개수가 같은 다음 수를 찾으면 반환
        if(n_1 == amount_of_one(i)) return i;
    }
}
