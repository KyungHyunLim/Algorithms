/*
2xn 타일링

memo[i] = ( memo[i-1] + memo[i-2] ) % 1000000007
*/
#include <string>
#include <vector>

using namespace std;

vector<int> memo;

int solution(int n) {
	int answer = 0;

	memo.push_back(1);
	memo.push_back(2);

	for (int i = 2; i < n; i++) {
		memo.push_back(memo[i-1] + memo[i-2]);
        memo[i] %= 1000000007;
	}
	return memo[n-1];
}
