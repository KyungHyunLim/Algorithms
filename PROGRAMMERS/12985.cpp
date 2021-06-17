/*
예상 대진표

* 현재 번호 + 1 / 2 값이 다음 라운드 번호가 됨

*/
#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
    // 바로 만났을 경우 1번
    int answer = 1;
    // 2로 나누어 가며 
    while(true){
        // 다음 대전번호가 동일할 경우 만난 것이므로 반복문 종료
        if((a+1)/2 == (b+1)/2) break;
        a = (a+1) / 2;
        b = (b+1) / 2;
        // 라운드 증가
        answer++;
    }
    return answer;
}
