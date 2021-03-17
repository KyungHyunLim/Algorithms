#define MIN(A,B) A>B?B:A
#define MAX(A,B) A<B?B:A

#include<iostream>
#include<vector>
#include<string.h>
#include<queue>

using namespace std;

int N, M, K;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;

    if (N == 0 || M == 0 || N + M <= K) {
        cout << 0;
        return 0;
    }

    int maximum_tems;
    if (2 * M >= N) {
        maximum_tems = N / 2;
    }
    else {
        maximum_tems = M;
    }

    //차출 인원이 없으면 최대팀 그대로 출력
    if (K == 0) {
        cout << maximum_tems;
    }
    //차출 인원이 있으면
    else {    
        int left_student = N + M - ((maximum_tems * 3));
        // 차출 인원이 팀 구성후 여유 인원 보다 
        // 적거나 같으면 최대 팀수 동일
        if (K <= left_student) {
            cout << maximum_tems;
        }
        // 많으면
        // 3명당 최대 팀 1개 감소
        else {
            K -= left_student;
            if (K % 3 == 0)  cout << maximum_tems - (K / 3);
            else  cout << maximum_tems - 1 - (K / 3);
        }
    }
    
    return 0;
}
