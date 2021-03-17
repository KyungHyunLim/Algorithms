#define _CRT_SECURE_NO_WARNINGS

#define MIN(A,B) A<B?A:B
#define ll long long

#include <iostream>
#include <cstring>
#include <queue>
#include <string.h>
#include <set>

using namespace std;

bool wall[8][8][11] = { true, };
vector<pair<int, int>> walls;
char map[8][8];

int dx[9] = { -1, -1, -1, 0, 0, 1, 1, 1, 0 };
int dy[9] = { -1, 0, 1, -1, 1, -1, 0, 1, 0 };

bool no_wall(int x, int T)
{
	for (int i = x - 1; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			if (wall[T][i][j] == false) return false;
		}
	}
	return true;
}

bool solve() {
	queue<pair<pair<int, int>,int>> q;
	q.push(make_pair(make_pair(7, 0),0));

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int now = q.front().second;
		q.pop();

		if (x == 0 && y == 7) return true;
		else {
			if (no_wall(x, now)) return true;
		}

		for (int i = 0; i < 9; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
				if (wall[now][nx][ny] && wall[now+1][nx][ny]) {
					q.push(make_pair(make_pair(nx, ny), now + 1));
				}
			}
		}
	}
	return false;
}

bool Wall_State()
{
	for (int i = 0; i < 7; i++)
	{
		int Cnt = 0;
		for (int j = 0; j < 8; j++)
		{
			if (map[i][j] == '#') Cnt++;
		}
		if (Cnt == 8) return false;
	}
	return true;
}

int main() {

	memset(wall, true, sizeof(wall));

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> map[i][j];
			if (map[i][j] == '#') {
				wall[0][i][j] = false;
				walls.push_back(make_pair(i, j));
			}
		}
	}

	if (walls.size() == 0) {
		cout << 1;
		return 0;
	}

	//시간이 지남에 따라 벽 위치 변경
	for (int i = 0; i < walls.size(); i++) {
		int x = walls[i].first;
		int y = walls[i].second;
		int time = 1;
		for (int j = x+1; j < 8; j++) {
			wall[time++][j][y] = false;
		}
	}
	
	if (!Wall_State()) {
		cout << 0;
		return 0;
	}

	if (solve()) cout << 1;
	else cout << 0;

	return 0;
}