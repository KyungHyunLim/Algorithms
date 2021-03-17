#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int arr[16];
int N;
int answer;

bool isok(int x) {
    for (int i = 0; i < x; i++) {
        if (arr[i] == arr[x] || abs(arr[x] - arr[i]) == x - i) return false;
    }
    return true;
}

void dfs(int x) {
    if (x == N) {
        answer++;
    }
    else {
        for (int i = 0; i < N; i++) {
            arr[x] = i;
            if (isok(x)) {
                dfs(x + 1);
            }
        }
    }
}

int main() {
       
    cin >> N;
    answer = 0;
    dfs(0);
    cout << answer;

    return 0;
}
