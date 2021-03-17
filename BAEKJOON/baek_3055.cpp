#define _CRT_SECURE_NO_WARNINGS

#define MIN(A,B) A<B?A:B

#include <iostream>
#include <cstring>
#include <queue>
#include <string.h>

using namespace std;

int R, C;
char map[51][51];
bool visited[51][51];
int dist[51][51];
vector<pair<int, int>> waters;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0, 1,-1 };

void water_spread() {
	queue<pair<int, int>> q;
	for (int i = 0; i < waters.size(); i++) {
		q.push(waters[i]);
		dist[waters[i].first][waters[i].second] = 0;
	}

	while (!q.empty()) {
		int water_size = q.size();
		for (int i = 0; i < water_size; i++) {
			int sx = q.front().first;
			int sy = q.front().second;
			q.pop();
			for (int j = 0; j < 4; j++) {
				int nx = sx + dx[j];
				int ny = sy + dy[j];

				//영역안이고
				if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
					//빈칸이고
					if (map[nx][ny] == '.') {
						//물차는 시간이 더 작으면
						if (dist[nx][ny] > dist[sx][sy] + 1) {
							dist[nx][ny] = dist[sx][sy] + 1;
							q.push(make_pair(nx, ny));
						}
					}
				}
			}
		}
	}
}

void hedgehog_move(int sx, int sy, int ex, int ey) {
	queue<pair<pair<int, int>, int>> q;
	q.push(make_pair(make_pair(sx, sy), 0));
	visited[sx][sy] = true;

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int n_cnt = q.front().second;
		q.pop();

		if (x == ex && y == ey) {
			cout << n_cnt << endl;
			return;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			//영역안이고
			if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
				//방문한적 없고
				if (!visited[nx][ny]) {
					//돌 아니고, 물찰예정인 곳이 아니면
					if (map[nx][ny] != 'X' && dist[nx][ny] > n_cnt + 1) {
						visited[nx][ny] = true;
						q.push(make_pair(make_pair(nx, ny), n_cnt + 1));
					}
				}
			}
		}
	}
	cout << "KAKTUS" << endl;
}

int main() {
	cin >> R >> C;

	int hedgehog_x;
	int hedgehog_y;

	int beaver_x;
	int beaver_y;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			char temp;
			cin >> temp;
			map[i][j] = temp;
			if (temp == 'S') {
				hedgehog_x = i;
				hedgehog_y = j;
			}
			if (temp == 'D') {
				beaver_x = i;
				beaver_y = j;
			}
			if (temp == '*') {
				waters.push_back(make_pair(i, j));
			}
			dist[i][j] = 1e9;
		}
	}

	water_spread();
	hedgehog_move(hedgehog_x, hedgehog_y, beaver_x, beaver_y);

	return 0;
}