#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
using namespace std;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	bool dp[101][1001];
	memset(dp, false, sizeof(dp));

	int N, S, M;
	cin >> N >> S >> M;

	int V[101];
	for (int i = 0; i < N; i++) {
		cin >> V[i];
	}

	dp[0][S] = true;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			if (dp[i - 1][j] == true) {
				if(j + V[i-1] <= M) dp[i][j + V[i-1]] = true;
				if(j - V[i-1] >= 0) dp[i][j - V[i-1]] = true;
			}
		}
	}

	int answer = -1;
	for (int i = M; i >= 0; i--) {
		if (dp[N][i]) {
			answer = i;
			break;
		}
	}

	cout << answer << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}