/*---------------------------------------------------------
제곱수 만들기
1. 소수구하기
2. 오름차순으로 소수 저장
3. 최소가 되는 B 구하기
  3-1. 제곱수면 종료
  3-2. 제곱수가 아니면 A를 소수로 계속 나눔
    3-2-1. 사용된 소수의 개수가 홀수면 현재 소수 한번 더 곱함
    3-2-2. A가 1이거나 현재 소수보다 작으면 종료
  3-3. A가 1보다 크면 A 한번더 곱함
4. 정답 출력
---------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
 
#include<iostream>
#include<math.h>
 
using namespace std;
 
int primes[3162];
int primes_sort[3162];
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
 
    scanf("%d", &T);
 
    //소수 구하기
    int p_cnt = 0;
    primes[0] = 2;
    for (int i = 2; i <= 3162; i++) {
        if (primes[i] == -1) continue;
        for (int j = i+i; j <= 3162; j+=i) {
            primes[j] = -1;
        }
    }
 
    for (int i = 2; i <= 3162; i++) {
        if (primes[i] != -1) {
            primes_sort[p_cnt] = i;
            p_cnt++;
        }
    }
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        int A;
        scanf("%d", &A);
 
        int result = 1;
         
        if (sqrt(A) != (int)(sqrt(A))) {
            for (int i = 0; i < p_cnt; i++) {
                int cnt = 0;
                while (!(A % primes_sort[i])) {
                    A = A / primes_sort[i];
                    cnt += 1;
                }
                if (cnt % 2 != 0) result *= primes_sort[i];
                if (A == 1 || primes_sort[i] > A) break;
            }
            if (A > 1) result *= A;
        }
 
        printf("#%d %d\n", test_case, result);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
