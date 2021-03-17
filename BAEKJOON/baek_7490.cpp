#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
using namespace std;

int N;

void solve(int sum, int sign, int num, int n, string s) {
	if (n == N) {
		sum += (num * sign);
		if (sum == 0) {
			cout << s << endl;
		}
	}
	else {
		solve(sum, sign, num*10 + (n + 1), n + 1, s + ' ' + char( n + 1 + '0'));
		solve(sum + (sign * num), 1, n + 1, n + 1, s + '+' + char(n + 1 + '0'));
		solve(sum + (sign * num), -1, n + 1, n + 1, s + '-' + char(n + 1 + '0'));
	}
}

int main() {
	int T;
	scanf("%d", &T);

	for (int test_case = 0; test_case < T; test_case++) {
		scanf("%d", &N);
		solve(0, 1, 1, 1, "1");
		printf("\n");
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
