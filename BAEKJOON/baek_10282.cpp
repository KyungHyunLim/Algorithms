#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int n, d, c;
vector<vector<int>> coms[10001];
bool visited[10001];
vector<int> dist(10001,1e9);

void dik(int node) {
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, node));
	dist[node] = 0;

	while (!pq.empty()) {
		int co = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		for (int i = 0; i < coms[cur].size(); i++) {
			int next_node = coms[cur][i][0];
			int next_cost = co + coms[cur][i][1];
			if (dist[next_node] > next_cost) {
				dist[next_node] =  next_cost;
				pq.push(make_pair(-next_cost, next_node));
			}
		}
	}
}


int main(int argc, char** argv)
{
	int T;
	cin >> T;

	for (int test_case = 0; test_case < T; test_case++) {
		memset(visited, false, sizeof(visited));
		fill(dist.begin(), dist.end(), 1e9);
		for (int i = 0; i < 10001; i++) {
			coms[i].clear();
		}

		cin >> n >> d >> c;
		for (int i = 0; i < d; i++) {
			int a, b, s;
			cin >> a >> b >> s;

			coms[b].push_back({ a, s });
		}
		
		dik(c);

		int answer = 0;
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			if (dist[i] != 1e9) {
				answer = MAX(answer, dist[i]);
				cnt++;
			}

		cout << cnt << " " << answer << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}