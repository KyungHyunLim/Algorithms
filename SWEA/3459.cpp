/*
승자예측하기

* long long 타입 사용(int 범위 초과)
* 동적계획법(메모이제이션)

*/
#include<iostream>
 
using namespace std;
 
long long arr[61];
 
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
     
    scanf("%d", &T);
     
    arr[1] = 1;
    arr[2] = 2;
    /*
    B 1 1
    A 4 2~5
    B 4 6~9
    A 16 10~25
    B 16 26~41
    ...
     
    */
    long long t = 4;
    for (int i = 3; i <= 60; i+=2) {
        arr[i] = arr[i - 1] + t;
        arr[i+1] = arr[i] + t;
        t *= (long long)4;
    }
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        long long N;
        scanf("%lld",&N);
 
        int i;
        for (i = 1; i <= 60; i++) {
            if (arr[i] > N) {
                break;
            }
        }
 
        if ((i-1) % 2 == 0) printf("#%d Alice\n", test_case);
        else printf("#%d Bob\n", test_case);
 
 
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
