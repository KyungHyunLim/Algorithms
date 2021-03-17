#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int connection;
	int cost;
};

vector<info> lags[100001];
bool visited[100001];

bool bfs(int c, int start_node, int end_node) {
	queue<int> q;
	memset(visited, false, sizeof(visited));
	q.push(start_node);
	visited[start_node] = true;
	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (int i = 0; i < lags[node].size(); i++) {
			info next = lags[node][i];
			int n_node = next.connection;
			int n_cost = next.cost;

			if (!visited[n_node] && n_cost >= c) {
				visited[n_node] = true;
				q.push(n_node);
			}
		}
	}

	return visited[end_node];
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	cin >> N >> M;

	int start = 1000000000;
	int end = 1;
	for (int i = 0; i < M; i++) {
		int A, B, C;
		cin >> A >> B >> C;
		
		lags[A].push_back({ B, C });
		lags[B].push_back({ A, C });
		start = MIN(start, C);
		end = MAX(end, C);
	}
	int s_node, e_node;
	cin >> s_node >> e_node;
	
	int answer = start;
	while (start <= end) {
		int mid = (start + end) / 2;
		if (bfs(mid, s_node, e_node)) {
			start = mid + 1;
			answer = MAX(answer, mid);
		}
		else {
			end = mid - 1;
		}
	}

	cout << answer << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}