#define _CRT_SECURE_NO_WARNINGS
#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>

using namespace std;

int N, M;
int map[1001][1001];
int visited[1001][1001];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int answer = 0;

void count(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M || visited[nx][ny] || map[nx][ny] != 0) continue;
		visited[nx][ny] = true;
		count(nx, ny);
		answer++;
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &map[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) {
				memset(visited, false, sizeof(visited));
				answer = 1;
				map[i][j] = 0;
				visited[i][j] = true;
				count(i, j);
				map[i][j] = answer % 10;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}

	return 0;
}
/*
#include<iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int map[1002][1002];
int n, m;
int visit[1002][1002];
int resultmap[1002][1002];

void visitClear()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			visit[i][j] = 0;
}

int cnt;
void dfs(int y, int x, int comType)
{
	cnt++;
	map[y][x] = comType;

	//상하좌우 ㄱㄱ
	if (y - 1 >= 0 && map[y - 1][x] == 0 && visit[y - 1][x] == 0)
	{
		visit[y - 1][x] = 1;
		dfs(y - 1, x, comType);
	}
	if (y + 1 < n && map[y + 1][x] == 0 && visit[y + 1][x] == 0)
	{
		visit[y + 1][x] = 1;
		dfs(y + 1, x, comType);
	}
	if (x-1 >= 0 && map[y][x - 1] == 0 && visit[y][x -1] == 0)
	{
		visit[y][x - 1] = 1;
		dfs(y, x - 1, comType);
	}
	if (x +1 < m && map[y][x + 1] == 0 && visit[y][x + 1] == 0)
	{
		visit[y][x + 1] = 1;
		dfs(y, x + 1, comType);
	}
}

int main()
{
	cin >> n >> m;

	// make map
	//벽을 -1, 공간을 0
	string temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		for (int j = 0; j < m; j++)
		{
			if((temp[j] -'0') == 1)
				map[i][j] = -1;
		}
	}

	//컴포넌트 자리 찾아주기
	vector<int>com = {0};
	int comtype = 0; // 1부터시작
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (map[i][j] == 0)
			{
				//dfs
				comtype++;
				cnt = 0;
				dfs(i, j, comtype);
				com.push_back(cnt);
			}

	//순회하며 컴포넌트 합쳐주기
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			//벽일때
			if (map[i][j] == -1)
			{
				//상하좌우의 컴포넌트 구해준거 다합쳐주기, 중복 조심
				int sum = 0;
				set<int> used;

				if (i - 1 >= 0 && map[i - 1][j] != -1)
				{
					used.insert(map[i - 1][j]);
					sum += com[map[i - 1][j]];
				}
				if (i + 1 < n && map[i + 1][j] != -1 && used.count(map[i + 1][j])==0)
				{
					used.insert(map[i + 1][j]);
					sum += com[map[i + 1][j]];
				}
				if (j - 1 >= 0 && map[i][j - 1] != -1 && used.count(map[i][j - 1]) == 0)
				{
					used.insert(map[i][j - 1]);
					sum += com[map[i][j - 1]];
				}
				if (j + 1 < m && map[i][j + 1] != -1 && used.count(map[i][j + 1]) == 0)
				{
					used.insert(map[i][j + 1]);
					sum += com[map[i][j + 1]];
				}
				resultmap[i][j] = (sum + 1)%10;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << resultmap[i][j];
		}
		cout << '\n';
	}


	return 0;
}
*/