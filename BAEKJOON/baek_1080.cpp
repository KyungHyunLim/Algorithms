#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int A[50][50];
int B[50][50];

void change(int x, int y) {

    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            A[i][j] = A[i][j] == 1 ? 0 : 1;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d",&A[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &B[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < N-2; i++) {
        for (int j = 0; j < M-2; j++) {
            if (A[i][j] != B[i][j]) {
                change(i , j);
                count++;
            }
        }
    }

    bool flag = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] != B[i][j]) {
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }

    if (flag) cout << count;
    else cout << -1;

    return 0;
}