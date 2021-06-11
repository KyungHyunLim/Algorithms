#include <iostream>
using namespace std;

int recursive_fibo(int n) {
    if (n <= 2) return 1;
    return recursive_fibo(n - 1) + recursive_fibo(n - 2);
}

int arr[11]{};
int memo_fibo(int n) {
    if (n <= 2) return 1;
    else if (arr[n] != 0) return arr[n];
    else {
        arr[n] = memo_fibo(n - 1) + memo_fibo(n - 2);
        return arr[n];
    }
}

int main() {
    int n = 10;

    // 재귀 사용
    int recursive_result = recursive_fibo(n);
    cout << "recursive_result:\t" << recursive_result << endl;

    // 반복문 사용
    int a = 1;
    int b = 1;
    for (int i = 2; i < n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    int iteration_result = b;
    cout << "iteration_result:\t" << iteration_result << endl;

    // 메모제이션(동적계획법)
    arr[1] = 1;
    arr[2] = 1;
    int memo_result = memo_fibo(n);
    cout << "memo_result:\t" << memo_result << endl;
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
