/*
혁진이의 프로그램 검증
방향(0 오른쪽 / 1 위 / 2 왼쪽 / 3 아래)

나머지는 문제 요구에 따라 구현.
핵심: 무한루프 검출 
모든 상태(좌표, 방향(0 오른쪽 / 1 위 / 2 왼쪽 / 3 아래), 메모리값 0~15)가 동일한데 반복되는 경우 무한루프
@를 만나야 프로그램이 종료될 수 있음
*/
#include<iostream>
#include<vector>
#include <cstring>
#include<queue>
using namespace std;

int R, C;
char command[21][21];
//좌표, 방향(0 오른쪽 / 1 위 / 2 왼쪽 / 3 아래), 메모리값 0~15
bool visited[21][21][4][16];
string ans;

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

struct node {
	int r;
	int c;
	int d;
	int v; // value;
	node(int _r, int _c, int _d, int _v) : r(_r), c(_c), d(_d), v(_v) {};
};

void bfs() {
	queue<node> q;
	q.push(node(0, 0, 0, 0));
	visited[0][0][0][0] = true;

	while (!q.empty()) {
		int r = q.front().r;
		int c = q.front().c;
		int direction = q.front().d;
		int value = q.front().v;
		q.pop();

		if (command[r][c] == '@') {
			ans = "YES";
			return;
		}

		char cmd = command[r][c];
		int new_direction = direction;
		int new_value = value;

		if (cmd == '<') new_direction = 2;
		else if (cmd == '>') new_direction = 0;
		else if (cmd == '^') new_direction = 1;
		else if (cmd == 'v') new_direction = 3;
		else if (cmd == '_') new_direction = value == 0 ? 0 : 2;
		else if (cmd == '|') new_direction = value == 0 ? 3 : 1;
		else if (cmd == '+') new_value = value + 1 == 16 ? 0 : value + 1;
		else if (cmd == '-') new_value = value - 1 == -1 ? 15 : value - 1;
		else if ('0' <= cmd && cmd <= '9') new_value = cmd - '0';
		if (cmd == '?')
		{
			for (int i = 0; i < 4; i++)
			{
				int nr = r + dx[i];
				int nc = c + dy[i];

				if (nr < 0) nr = R - 1;
				else if (nr == R) nr = 0;
				if (nc < 0) nc = C - 1;
				else if (nc == C) nc = 0;

				if (visited[nr][nc][i][new_value] == false)
				{
					visited[nr][nc][i][new_value] = true;
					q.push(node(nr,nc,i,new_value));
				}
			}
		}
		else
		{
			int nr = r + dx[new_direction];
			int nc = c + dy[new_direction];

			if (nr < 0) nr = R - 1;
			else if (nr == R) nr = 0;
			if (nc < 0) nc = C - 1;
			else if (nc == C) nc = 0;

			if (visited[nr][nc][new_direction][new_value] == false)
			{
				visited[nr][nc][new_direction][new_value] = true;
				q.push(node(nr, nc, new_direction, new_value));
			}
		}
	}
	ans = "NO";
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(visited, false, sizeof(visited));
		cin >> R >> C;

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> command[i][j];
			}
		}
		
		bfs();

		cout << "#" << test_case << " " << ans << endl;

	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
