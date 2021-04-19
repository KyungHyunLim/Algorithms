/*
탈주범 검거

- 주의 할점 -
1. 카운팅시 맨홀뚜껑 지역 포함
2. 맨홀 뚜껑이 1시간
3. 파이프가 없는곳, 연결되지 않은 파이프는 이동 불가
--------------------------------------------------

0. 파이프 이동 가능 방향 및 연결된 파이프 정의
1. bfs로 탐색
  1.1 맵밖, 중복방문, 연결된 파이프?, 시간초 조건 주의 탐색
  1.2 탐색 성공시 개수 증가
*/

#define _CRT_NO_SECURE_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;


// NxM 맵크기
// (R, C) 맨홀 뚜껑 위치
// L시간 후 가능한 위치
int N, M, R, C, L;

// 맵정보
int map[50][50];
// 탐색용 중복 방문 방지
bool visited[50][50];
// 탈주범이 있을 수 있는 곳 위치 개수
int c;

// 파이프별 이동 가능 방향
vector<int> pipes[8] = { {},
	{0, 1, 2, 3}, // 1. 상하좌우
	{0, 1}, // 2. 상하
	{2, 3}, // 3. 좌우
	{0, 3}, // 4. 상우
	{1, 3}, // 5. 하우
	{1, 2}, // 6. 하좌
	{0, 2}, // 7. 상좌
};

// 0: 상, 1: 하, 2: 좌, 3: 우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int connected[4][8] = {
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 1, 0, 0, 1},
	{0, 1, 0, 1, 1, 1, 0, 0},
	{0, 1, 0, 1, 0, 0, 1, 1}
};

void search(int x, int y) {
	queue<pair<int, pair<int, int>>> q;
	q.push(make_pair(1,make_pair(x, y)));
	visited[x][y] = true;

	while (!q.empty()) {
		int l = q.front().first;
		int cx = q.front().second.first;
		int cy = q.front().second.second;
		int kind = map[cx][cy];
		visited[cx][cy] = true;
		q.pop();

		// 시간 초가 지나면 못감
		if (l >= L) continue;

		for (int i = 0; i < pipes[kind].size(); i++) {
			int nx = cx + dx[pipes[kind][i]];
			int ny = cy + dy[pipes[kind][i]];
			// 맵밖으로 벗어 나지 못함
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			// 중복방문할 필요 없음
			if (visited[nx][ny]) continue;
			// 파이프가 아니면 못감
			if (map[nx][ny] == 0) continue;
			// 연결된 파이프가 아니면 못감
			if (!connected[pipes[kind][i]][map[nx][ny]]) continue;
			
			//printf("L-%d, Loc-(%d,%d), Pipe-%d, Dir-%d, New_Loc-(%d, %d), New_Pipe-%d\n", l, cx, cy, map[cx][cy], pipes[kind][i], nx, ny, map[nx][ny]);
			//cout << connected[pipes[kind][i]][map[nx][ny]] << endl;
			// q에 넣기
			q.push(make_pair(l + 1, make_pair(nx, ny)));
			// 방문 표시
			visited[nx][ny] = true;
			// 갈수 있는 곳이 늘었으므로 개수 증가
			c++;
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M >> R >> C >> L;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> map[i][j];
			}
		}
		
		memset(visited, false, sizeof(visited));
		c = 1;
		//printf("L-%d, Loc-(%d,%d), Pipe-%d\n", 1, R, C, map[R][C]);
		search(R, C);

		cout << "#" << test_case << " " << c << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
/*
1
5 6 2 1 3
0 0 5 3 6 0
0 0 2 0 2 0
3 3 1 3 7 0
0 0 0 0 0 0
0 0 0 0 0 0
*/
