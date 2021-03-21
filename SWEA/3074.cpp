/*
10^9의 매우 큰 범위의 탐색 필요 => 이분 탐색 활용

1. 중간 값을 이용해 해당 시간에서 처리 가능한 사람의 수 계산
2. 처리 가능한 사람 수가 주어진 수에 비해 적은지 많은지에 따라 탐색 범위 조절
3. start가 탐색 범위의 시작보다 커질때 까지 1-2 반복
*/

#define MAX(x,y) x>y ? x:y;
#define MIN(x,y) x<y ? x:y;
 
#include<iostream>
 
using namespace std;
 
long long tk[100001];
long long max_time;
long long M, N;
 
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
 
    cin >> T;
 
    for (test_case = 1; test_case <= T; ++test_case)
    {
        max_time = -1;
        scanf("%d %d", &N, &M);
 
        for (int i = 0; i < N; i++) {
            scanf("%d", &tk[i]);
            max_time = MAX(max_time, tk[i]);
        }
 
        long long total_time = M*max_time;
        long long start_time = 0;
        long long mid;
        long long min = total_time;
 
        while (start_time <= total_time) {
            mid = (start_time + total_time) / 2;
            long long res = 0;
            for (int i = 0; i < N; i++) {
                res += (mid / tk[i]);
            }
             
            if (res >= M) {
                if (mid < min) {
                    min = mid;
                }
                total_time = mid - 1;
            }
            else {
                start_time = mid + 1;
            }
        }
        printf("#%d %lld\n", test_case, min);
 
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
