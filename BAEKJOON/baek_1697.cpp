#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int arr[100001] = {0,};
int answer;

void bfs(int V, int K) {
	queue<int> q;
	q.push(V);

	while (!q.empty()) {
		int node = q.front();
		q.pop();	
		if (node == K) {
			answer = arr[node];
			return;
		}
		for (int i = 0; i < 3; i++) {
			int next;
			if (i == 0) next = node + 1;
			else if (i == 1)next = node - 1;
			else next = node * 2;
			if (0 <= next && next < 100001 && !arr[next]) {
				arr[next] = arr[node] + 1;
				q.push(next);
			}
		}
		
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, K;
	cin >> N >> K;

	answer = 0;
	
	bfs(N, K);

	cout << answer << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}