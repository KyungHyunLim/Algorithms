#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int arr[1001];

int main() {

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + N);

    int answer = 0;
    int c_sum = 0;
    for (int i = 0; i < N; i++) {
        c_sum += arr[i];
        answer += c_sum;
    }

    cout << answer;

    return 0;
}
