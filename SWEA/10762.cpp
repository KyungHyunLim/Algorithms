/*
사탕나누기

동일한 수를 bitwise XOR 계산시 0
즉, 투정없이 나누고, 최대한 사탕을 많이 가져가기 위해서는 
<가장 작은 값 = 나머지 XOR 연산 값>
이 되어야 한다.

1. 입력을 받으면서 최소값, 전체개수합 구하기 및 bitwise XOR 연산
2. 연산 결과가 0이면 
  2-1. 전체 개수 - 최소 값
   아니면
  2-2. No
*/

#include<iostream>
 
using namespace std;
 
int sum;
int possible;
int N;
int max_ans;
int temp;
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
 
    scanf("%d", &T);
 
    for (test_case = 1; test_case <= T; ++test_case)
    {       
        scanf("%d", &N);
 
        sum = 0;
        max_ans = 10000009;
        for (int i = 0; i < N; i++) {
            scanf("%d", &temp);
            sum += temp;
 
            possible = (i == 0) ? temp : possible ^ temp;
            max_ans = max_ans > temp ? temp : max_ans;
        }
 
        possible != 0 ? printf("#%d NO\n", test_case) : printf("#%d %d\n", test_case, sum - max_ans);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
