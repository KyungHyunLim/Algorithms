/*
Dp 연습. 오르막수

마지막 숫자에 대해 올수있는것 다 더해주기.

*/
void f_11057() {
	int n;
	cin >> n;

	int dp[1001][10];
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < 10; i++) {
		dp[1][i] = 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = j; k <= 9; k++) {
				dp[i][k] += dp[i - 1][j];
				dp[i][k] %= 10007;
			}
		}
	}

	int answer = 0;
	for (int i = 0; i < 10; i++) {
		answer += dp[n][i];
	}

	cout << answer % 10007 << endl;
}
