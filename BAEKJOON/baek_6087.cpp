#define _CRT_SECURE_NO_WARNINGS

#define MIN(A,B) A<B?A:B

#include <iostream>
#include <cstring>
#include <queue>
#include <string.h>

using namespace std;

int R, C;
char map[100][100];
bool visited[100][100];
int dist[100][100];
vector<pair<int, int>> points;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0, 1,-1 };

struct info {
	int x;
	int y;
};

void move(int sx, int sy) {
	queue<info> q;
	q.push({sx, sy});
	visited[sx][sy] = true;
	dist[sx][sy] = 0;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			//영역안이고
			while (nx >= 0 && nx < C && ny >= 0 && ny < R) {
				//벽이면 그만 전진
				if (map[nx][ny] == '*') break;
				//방문한적 없고
				if (!visited[nx][ny]) {			
					visited[nx][ny] = true;
					dist[nx][ny] = dist[x][y] + 1;
					q.push({ nx,ny });
				}
				nx += dx[i];
				ny += dy[i];
			}
		}
	}
}

int main() {
	cin >> R >> C;

	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			char temp;
			cin >> temp;
			map[i][j] = temp;
			if (temp == 'C') {
				points.push_back(make_pair(i, j));
			}
		}
	}

	move(points[0].first, points[0].second);
	cout << dist[points[1].first][points[1].second] - 1;

	return 0;
}