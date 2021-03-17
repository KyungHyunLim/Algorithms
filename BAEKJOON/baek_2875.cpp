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

    //���� �ο��� ������ �ִ��� �״�� ���
    if (K == 0) {
        cout << maximum_tems;
    }
    //���� �ο��� ������
    else {    
        int left_student = N + M - ((maximum_tems * 3));
        // ���� �ο��� �� ������ ���� �ο� ���� 
        // ���ų� ������ �ִ� ���� ����
        if (K <= left_student) {
            cout << maximum_tems;
        }
        // ������
        // 3��� �ִ� �� 1�� ����
        else {
            K -= left_student;
            if (K % 3 == 0)  cout << maximum_tems - (K / 3);
            else  cout << maximum_tems - 1 - (K / 3);
        }
    }
    
    return 0;
}
