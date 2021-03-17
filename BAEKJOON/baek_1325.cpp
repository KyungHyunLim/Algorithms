#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<string.h>
#include<vector>

using namespace std;

vector<int> computers[10001];
bool visited[10001];
int c;
vector<int> answer;
int max_ans;

void dfs(int x) {
	c++;
	max_ans = MAX(c, max_ans);
	visited[x] = true;

	for (int i = 0; i < computers[x].size(); i++) {
		if (!visited[computers[x][i]]) {
			dfs(computers[x][i]);
		}
	}
}

int main(int argc, char** argv)
{
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;

		computers[b].push_back(a);
	}

	max_ans = 0;

	for (int i = 1; i <= N; i++) {
		c = 0;
		memset(visited, false, sizeof(visited));
		dfs(i);
		answer.push_back(c);
	}
	
	for (int i = 0; i < answer.size(); i++) {
		if (max_ans == answer[i]) cout << (i + 1) << " ";
	}
	

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}