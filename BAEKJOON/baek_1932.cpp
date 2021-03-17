#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
int arr[501][501];
int dp[501][501];

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i + 1; j++) {
			cin >> arr[i][j];
		}
	}

	if (N == 1) {
		cout << arr[0][0] << endl;
		return 0;
	}
	else if(N==2) {
		int a = arr[0][0] + arr[1][0];
		int b = arr[0][0] + arr[1][1];
		cout << max(a, b) << endl;
	}
	else {
		int answer = 0;

		dp[0][0] = arr[0][0];
		dp[1][0] = arr[0][0] + arr[1][0];
		dp[1][1] = arr[0][0] + arr[1][1];

		for (int i = 2; i < N; i++) {
			for (int j = 0; j < i + 1; j++) {
				if (j == 0) {
					dp[i][j] = max(dp[i - 1][j] + arr[i][j], 0);
				}
				else {
					dp[i][j] = max(dp[i - 1][j - 1] + arr[i][j], dp[i - 1][j] + arr[i][j]);
				}
				answer = max(answer, dp[i][j]);
			}
		}

		cout << answer << endl;
	}

	return 0;
}