/*
정사각형의 방

핵심: 
1. 한방에서 갈수 있는 곳은 1개 => 같은 방을 두번 방문할 필요는 없다.
2. 갈수있는 방이 +1이므로 4번의 이동가능 수 = 3번의 이동가능수 + 1 이다.

전형적인 DP문제 이지만, 다르게 풀어보기 도전
BFS() 사용 => 작은수 부터 탐색 시작하면 풀이 가능
범위가 1,000,000이라 작은수 부터 접근 할수 있는 방법 필요 (배열 선언은 크기 한계로 불가)
Priority_queue 사용 예정

*/
#include<iostream>
#include<vector>
#include <cstring>
#include<queue>
using namespace std;

#define INF 987654321

int N;
int map[1000][1000];
bool visited[1000][1000];
int cnt;
int ans;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
/*
1
2
2 3
1 4
*/
struct info {
	int x;
	int y;
	int cnt;
	int start;
	info(int _x, int _y, int _cnt, int _start) : x(_x), y(_y), cnt(_cnt), start(_start){};
};

void solve(int i, int j) {
	queue<info> q;
	q.push(info(i,j,1, map[i][j]));
	visited[i][j] = true;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int c = q.front().cnt;
		int start = q.front().start;
		q.pop();
		
		if (c > cnt) {
			ans = start;
			cnt = c;
		}
		else if(c==cnt) {
			if (ans > start) {
				ans = start;
			}
		}

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[nx][ny]) continue;
			if (map[x][y] + 1 == map[nx][ny]) {
				visited[nx][ny] = true;
				q.push(info(nx, ny, c + 1, start));
			}
		}
	}
}

struct cmp {
	bool operator()(info t, info u) {
		return t.start > u.start;
	}
};

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
		char sequence[1000001][2];

		cin >> N;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				sequence[map[i][j]][0] = i + '0';
				sequence[map[i][j]][1] = j + '0';
			}
		}
	
		ans = INF;
		cnt = 0;
		for (int i = 1; i <= N * N; i++) {
			if (!visited[sequence[i][0]-'0'][sequence[i][1] - '0'])
				solve(sequence[i][0] - '0', sequence[i][1] - '0');
		}
		

		cout << "#" << test_case << " " << ans  << " " << cnt << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
