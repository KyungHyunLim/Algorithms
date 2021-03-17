#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

bool start_0[100001];
bool start_1[100001];
bool target[100001];
int N;

void change(bool A[], int sw) {
    for (int i = -1; i < 2; i++) {
        if (sw + i >= 0 && sw + i < N) {
            A[sw + i] = !A[sw + i];
        }
    }
}

bool compare(bool A[]) {
    for (int i = 0; i < N; i++) {
        if (A[i] ^ target[i]) return false;
    }
    return true;
}

int main() {

    cin >> N;
    
    for (int i = 0; i < N; i++) {
        int temp;
        scanf("%1d", &temp);
        start_0[i] = start_1[i] =  temp == 1 ? true : false;
    }

    for (int i = 0; i < N; i++) {
        int temp;
        scanf("%1d", &temp);
        target[i] = temp == 1 ? true : false;
    }

    change(start_0, 0);

    int cnt_0 = 1;
    int cnt_1 = 0;
    for (int i = 1; i < N; i++) {
        if (start_0[i - 1] != target[i - 1]) {
            change(start_0, i);
            cnt_0++;
        }
        if (start_1[i - 1] != target[i - 1]) {
            change(start_1, i);
            cnt_1++;
        }
    }

    int answer = -1;
    if (compare(start_0)) {
        answer = cnt_0;
    }
    else if (compare(start_1)) {
        answer = cnt_1;
    }

    if (compare(start_0) && compare(start_1)) answer = cnt_0 < cnt_1 ? cnt_0 : cnt_1;

    cout << answer;   

    return 0;
}