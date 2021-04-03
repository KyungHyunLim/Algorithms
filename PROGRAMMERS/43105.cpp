/*
정수 삼각형

dp[i][j] = i,j까지의 최대 합 

*/
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
	int answer = 0;
	int d[500][500] = { 0 };

	int n = triangle.size();
	d[0][0] = triangle[0][0];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			d[i][j] = d[i - 1][j] + triangle[i][j];
			if(j-1>=0 && d[i][j] < d[i - 1][j-1] + triangle[i][j])
				d[i][j] = d[i - 1][j-1] + triangle[i][j];
		}
	}

	answer = d[n - 1][0];
	for (int i = 0; i < n; i++) {
		if (answer < d[n - 1][i])
			answer = d[n - 1][i];
	}

	return answer;
}
