#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<int> graph[1001];
bool visit[1001];
vector<int> answer;
void dfs(int V) {
	answer.push_back(V);
	visit[V] = true;

	for (int i = 0; i < graph[V].size(); i++) {
		int node = graph[V][i];
		if (!visit[node]) dfs(node);
	}
}

void bfs(int V) {
	queue<int> q;
	q.push(V);

	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if (!visit[node]) {
			visit[node] = true;
			answer.push_back(node);
			for (int i = 0; i < graph[node].size(); i++) {
				int temp = graph[node][i];
				if (!visit[temp]) q.push(temp);
			}
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M, V;
	cin >> N >> M >> V;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;

		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	for (int i = 0; i < N; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	memset(visit, false, sizeof(visit));
	dfs(V);

	memset(visit, false, sizeof(visit));
    bfs(V);

	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i];
		if (!(i == (answer.size()/2) - 1 || i == answer.size() - 1)) cout << " ";
		if (i == (answer.size() / 2) - 1 || i == answer.size() - 1) cout << endl;
	}
	

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}