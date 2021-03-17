#define _CRT_SECURE_NO_WARNINGS

#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<string.h>
#include<queue>
#include<map>
#include<vector>

using namespace std;

int N;
int cheese[101][101]; // NxN 치즈
int visited[101][101]; // 덩어리 검색용 (BFS)
int answer;

void fairy_attack(map<int, vector<pair<int, int>>> &cheese_info, int day) {
	for (auto& c : cheese_info[day]) {
		cheese[c.first][c.second] = 0;
	}
}

int calc_sub_cheese() {
	memset(visited, 0, sizeof(visited));

	int amount = 0;

	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	queue<pair<int, int>> q;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j]) continue;
			visited[i][j] = 1;
			
			if (cheese[i][j] == 0) continue;
			amount++;
			
			q.push({ i,j });

			while (!q.empty()) {
				int x = q.front().first;
				int y = q.front().second;
				q.pop();

				for (int z = 0; z < 4; z++) {
					int newX = x + dx[z];
					int newY = y + dy[z];

					//치즈 영역 밖, 이미 방문, 없는 부분
					if (newX < 0 || newY < 0 || newX >= N || newY >= N || visited[newX][newY] || cheese[newX][newY] == 0) continue;
					
					visited[newX][newY] = 1;
					q.push({newX,newY});
				}
			}
		}
	}
	return amount;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		answer = 1;
		memset(visited, 0, sizeof(visited));

		scanf("%d", &N);

		int max_day = 0;
		map<int, vector<pair<int, int>>> cheese_info;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &cheese[i][j]);
				cheese_info[cheese[i][j]].push_back({ i,j });
				max_day = MAX(max_day, cheese[i][j]);
			}
		}

		for (int i = 1; i <= max_day; i++) {
			fairy_attack(cheese_info, i);
			answer = MAX(answer, calc_sub_cheese());
		}

		printf("#%d %d\n", test_case, answer);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}