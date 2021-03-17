#include<iostream>
#include<string.h>
#include<vector>

using namespace std;

int** map;
bool **visit;
int answer;
int N, M, K;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void dfs(int x, int y) {
	answer++;
	visit[x][y] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M || (!visit[nx][ny] && map[nx][ny])) continue;
		dfs(nx,ny);
	}
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;

	for (int test_case = 0; test_case < T; test_case++) {
		cin >> M >> N >> K;

		visit = (bool**)malloc(N * sizeof(bool*));
		map = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < M; i++) {
			visit[i] = (bool*)malloc(M * sizeof(bool));
			map[i] = (int*)malloc(M * sizeof(int));
			memset(visit[i], true, sizeof(visit[i]));
			memset(visit[i], 0, sizeof(visit[i]));
		}
		//

		for (int i = 0; i < K; i++) {
			int a, b;
			cin >> a >> b;

			map[a][b] = 1;
			visit[a][b] = false;
		}

		answer = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] && !visit[i][j]) {
					dfs(i, j);
					answer++;
				}
			}
		}
		
		cout << answer << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}