#define MAX(A,B) A>B?A:B;
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

long long int nums[11];
int N;
long long int max_ = -1e18 * 9;
long long int min_ = 1e18  * 9;

char itoch(int i) {
    switch (i)
    {
    case 0: return '+';
    case 1: return '-';
    case 2: return '*';
    case 3: return '/';
    default:
        break;
    }
}

long long int sub(long long int a, long long int b, char sign) {
    switch (sign)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        break;
    }
}

long long int calc(string result) {
    long long int s = sub(nums[0], nums[1], result[0]);
    for (int i = 2; i < N; i++) {
        s = sub(s, nums[i], result[i-1]);
    }
    return s;
}

void solution(int count, int target, int* signs, string result) {
    if (count == target-1) {
        long long int c = calc(result);
        max_ = MAX(c, max_);
        min_ = MIN(c, min_);
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (signs[i] == 0) continue;
            signs[i] --;
            solution(count + 1, target, signs, result + itoch(i));
            signs[i] ++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }
    int signs[4];
    //+ - x /
    for (int i = 0; i < 4; i++) {
        cin >> signs[i];
    }

    solution(0, N, signs, "");

    cout << max_ << endl;
    cout << min_ << endl;

    return 0;
}
