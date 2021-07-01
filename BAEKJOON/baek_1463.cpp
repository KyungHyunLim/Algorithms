/*
Dp 연습. 1로 만들기
*/
#include <iostream>

using namespace std;

int dp[1000001];

int main() {
	int n;
	cin >> n;
	
	dp[0] = dp[1] = 0;
	for (int i = 2; i <= n; i++) {
		/* +1로 온 경우 
		   *2로 온 경우
		   *3로 온 경우
		   dp에 최소 계산 개수 저장
		*/
		dp[i] = dp[i - 1] + 1;
		if (i % 2 == 0) dp[i] = dp[i] > (dp[i / 2] + 1) ? (dp[i / 2] + 1) : dp[i];
		if (i % 3 == 0) dp[i] = dp[i] > (dp[i / 3] + 1) ? (dp[i / 3] + 1) : dp[i];
	}

	cout << dp[n] << endl;

	return 0;
}
