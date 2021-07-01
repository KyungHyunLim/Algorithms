/*
Dp 연습. 쉬운 계단수

이전 숫자에서 -1, +1 부분이 더해짐

*/
void f_10844() {
  int n;
  cin >> n;

  long dp[101][10];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i < 10; i++) {
    dp[1][i] = 1;
  }

  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 0) dp[i][j] = dp[i - 1][j + 1];
      else if (j == 9) dp[i][j] = dp[i - 1][j - 1];
      else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
      dp[i][j] %= 1000000000;
    }
  }

  long aswner = 0;
  for (int i = 0; i < 10; i++) aswner += dp[n][i];

  cout << aswner % 1000000000 << endl;
}
